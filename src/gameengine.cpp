#include "gameengine.h"
#pragma region Lifecycle
void GameEngine::init(int fps, std::string windowTitle, int width, int height) {
	if (fps > 0) {
		this->frameDelay = 1000 / fps;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Initialization error", "Could not initialize game engine.", NULL);
		return;
	}
	if (TTF_Init() != 0) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Initialization error", "Could not initialize SDL_TTF.", NULL);
		return;
	}
	this->window = new Window(windowTitle, width, height);
	if(window->initWindow()){
		this->initManagers();
		this->initComponentManagers();
		this->initUniqueComponents();
		this->initSystems();
	}
}

void GameEngine::run() {
	if (window == nullptr) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Runtime error", "Please initialize engine before executing run.", NULL);
		std::cout << "Runtime error: Please initialize engine before executing run." << std::endl;
		return;
	}

	while (true)
	{
		Uint32 startTimestamp = SDL_GetTicks();

		inputManager->update();
		if (inputManager->interrupted) break;

		physicSystem->update();
		uiManager->update();

		audioSystem->update();
		renderSystem->update();
		Uint32 endTimestamp = SDL_GetTicks();
		Uint32 delay = (Uint32)(frameDelay - (endTimestamp - startTimestamp));
		SDL_Delay(delay);
	}
}

void GameEngine::quit() {
	TTF_Quit();
	SDL_Quit();
}

#pragma endregion Lifecycle
Entity GameEngine::addEntity(SDL_Point position) {
	Entity entity = entityManager->createEntity();
	Position* pos = this->posManager->addComponent(entity);
	if (pos != nullptr) {
		pos->setEntity(entity);
		pos->setPosition(position.x, position.y);
	}
	else {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Entity Initialization error", "Could not add position component to entity.", NULL);
	}
	return entity;
}

void GameEngine::setCameraFollowTarget(Entity e) {
	this->cameraFollow->setEntity(e);
	this->renderSystem->setCameraFollowTarget(cameraFollow);
}

void GameEngine::resetCameraFollowTarget() {
	this->setCameraFollowTarget({ 0 });
}

Entity GameEngine::addPlayer(SDL_Point position, unsigned int movementSpeed) {
	Entity player = addEntity(position);
	this->playerMovement->setEntity(player);
	this->playerMovement->setMovementSpeed(movementSpeed);
	return player;
}

// TODO: change to scene
void GameEngine::setTilemap(const char* tilesetFilePath, const char* tilemapDataFilePath, size_t layerCount) {
	Tilemap* tilemap = renderSystem->setMap("../TestTextures/test_level_1.png", "../TestTextures/test_level_1.json", layerCount);

	// create collision objects
	if (tilemap->hasCollisionLayer()) {
		int collisionLayerIndex = tilemap->getCollisionLayerIndex();
		std::vector<unsigned int> layer = tilemap->getLayer(collisionLayerIndex);
		int tileWidth = tilemap->getTileWidth();
		int tileHeight = tilemap->getTileHeight();
		int maxTilesPerRow = tilemap->getTilesPerRow();
		int currentDestX = 0;
		int currentDestY = 0;


		for (size_t i = 0; i < layer.size(); i++) {
			// checks if current x-position is greater or equals to max tilecount in row
			if (currentDestX >= maxTilesPerRow) {
				currentDestX = 0;
				currentDestY = currentDestY + 1;
			}

			// has collision entity
			if (layer[i] != 0) {
				int newX = currentDestX * tileWidth + (tileWidth/2);
				int newY = currentDestY * tileHeight + (tileHeight/2);
				Entity e = this->addEntity({ newX, newY });
				this->addColliderComponent(e, { 0,0 }, { tileWidth, tileHeight }, false);
			}
			currentDestX = currentDestX + 1;
		}
	}
}

void GameEngine::setBGM(const char* bgmFilePath) {
	audioSystem->addBGM(bgmFilePath);
	audioSystem->playBGM();
}

Sprite* GameEngine::addSpriteComponent(Entity e, const char* filePath, SDL_Point size, float scale) {
	Sprite* spriteComponent = spriteManager->addComponent(e);
	if (spriteComponent != nullptr) {
		spriteComponent->setEntity(e);
		spriteComponent->init(filePath, size.x, size.y, scale);
	}
	else {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Component Initialization error", "Could not add sprite component.", NULL);
	}
	return spriteComponent;
}

Collider* GameEngine::addColliderComponent(Entity e, SDL_Point offset, SDL_Point size, bool isTrigger) {
	Collider* colliderComponent = colliderManager->addComponent(e);
	if (colliderComponent != nullptr) {
		colliderComponent->setEntity(e);
		Position* positionComponent = posManager->getComponent(e);
		colliderComponent->init(positionComponent->x(), positionComponent->y(), offset.x, offset.y, size.x, size.y, isTrigger);
	}
	else {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Component Initialization error", "Could not add collider component.", NULL);
	}
	return colliderComponent;
}

Audio* GameEngine::addAudioComponent(Entity e) {
	Audio* audioComponent = audioManager->addComponent(e);
	if (audioComponent != nullptr) {
		audioComponent->setEntity(e);
	}
	else {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Component Initialization error", "Could not add audio component.", NULL);
	}
	return audioComponent;
}

size_t GameEngine::addAudioClip(Entity e, const char* filePath) {
	Audio* audioComponent = audioManager->getComponent(e);
	if (audioComponent != nullptr) {
		size_t audioIndex = audioComponent->addAudioClip(filePath);
		return audioIndex;
	}
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "AudioClip Initialization error", "Could not add audio clip to component.", NULL);
	return SIZE_MAX;
}

Animator* GameEngine::addAnimatorComponent(Entity e) {
	Animator* animator = animatorManager->addComponent(e);
	if (animator != nullptr) {
		animator->setEntity(e);
	}
	else {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Component Initialization error", "Could not add animator component.", NULL);
	}
	return animator;
}

void GameEngine::addAnimation(Entity e, const char* animationName, int frames, int frameDelayMS, const char* filePath) {
	Animator* animator = animatorManager->getComponent(e);
	animator->addAnimation(animationName, frames, frameDelayMS, FileLoader::loadTexture(filePath, this->window->getRenderer()));
}

void GameEngine::addAnimation(Entity e, const char* animationName, int frames, int frameDelayMS) {
	Animator* animator = animatorManager->getComponent(e);
	animator->addAnimation(animationName, frames, frameDelayMS);
}

#pragma region Getters
Position* GameEngine::getPositionComponent(Entity e){
	Position* result = this->posManager->getComponent(e);
	return result;
}

Sprite* GameEngine::getSpriteComponent(Entity e) {
	Sprite* result = this->spriteManager->getComponent(e);
	return result;
}

Collider* GameEngine::getColliderComponent(Entity e){
	Collider* result = this->colliderManager->getComponent(e);
	return result;
}

Audio* GameEngine::getAudioComponent(Entity e){
	Audio* result = this->audioManager->getComponent(e);
	return result;
}

Animator* GameEngine::getAnimatorComponent(Entity e){
	Animator* result = this->animatorManager->getComponent(e);
	return result;
}

Movement* GameEngine::getPlayerMovementComponent(Entity e){
	return playerMovement;
}
#pragma endregion Getters

#pragma region Initialization
void GameEngine::initManagers() {
	this->entityManager = new EntityManager();
	this->inputManager = new InputManager();
	this->uiManager = new UIManager(window->getRenderer(), inputManager);
}

void GameEngine::initComponentManagers() {
	this->spriteManager = new ComponentManager<Sprite>();
	this->posManager = new ComponentManager<Position>();
	this->animatorManager = new ComponentManager<Animator>();
	this->audioManager = new ComponentManager<Audio>();
	this->colliderManager = new ComponentManager<Collider>();
}

void GameEngine::initUniqueComponents() {
	this->playerMovement = new Movement();
	this->cameraFollow = new CameraFollow();
}

void GameEngine::initSystems() {
	this->renderSystem = new RenderSystem(spriteManager, posManager, this->window->getRenderer(), animatorManager, uiManager, colliderManager);
	this->renderSystem->initCamera(this->window->getWindowWidth(), this->window->getWindowHeight());
	//this->renderSystem->initCamera(640, 360);
	this->renderSystem->debugging(true);

	this->physicSystem = new PhysicSystem(inputManager, playerMovement, posManager, spriteManager, animatorManager, colliderManager);

	this->audioSystem = new AudioSystem(audioManager);
	this->audioSystem->init();
}
#pragma endregion Initialization