#include "rendersystem.h"
/**
* @brief Constructor for RenderSystem objects to set needed references.
* @param frameDelay - Delay between frames.
* @param spriteManager - Reference to the sprite manager for sprite objects.
* @param positionManager  - Reference to the position manager for position objects.
* @param renderer - Reference to the SDL_Renderer for the actual rendering of the sprites in the gameworld.
* @param cameraFollow - Camera follow for rendering of 2d camera.
* @param animatorManager - Animator manager to animate the sprites with an animator component.
 *@param uiManager - UIManager to be able to render the ui elements.
*/
RenderSystem::RenderSystem(int frameDelay, ComponentManager<Sprite>* spriteManager, ComponentManager<Position>* positionManager, SDL_Renderer* renderer,
	ComponentManager<Animator>* animatorManager, UIManager* uiManager, ComponentManager<Collider>* colliderManager, ComponentManager<EnemyMovement>* enemyMovementManager) {
	this->frameDelay = frameDelay;
	this->positionManager = positionManager;
	this->spriteManager = spriteManager;
	this->renderer = renderer;
	this->animatorManager = animatorManager;
	this->uiManager = uiManager;
	this->colliderManager = colliderManager;
	this->enemyMovementManager = enemyMovementManager;
}

/**
* @brief Render system update loop. Iterates over every sprite object and renders the texture to the position of the entity holding the sprite.	
*/
void RenderSystem::update() {
	// clear renderer
	SDL_RenderClear(renderer);
	moveCamera();

	renderTilemap();
	renderSprites();

	debugPosition();
	debugColliders();
	debugEnemyPathing();

	renderUI();

	render();
}
/**
 * @brief Render the current textures of the renderer.
*/
void RenderSystem::render() {
	SDL_RenderPresent(renderer);
}

/**
* @brief Debug function that visualizes the position.
*/
void RenderSystem::debugPosition() {
	if (debug) {
		size_t componentCount = positionManager->getComponentCount();

		for (size_t i = 0; i < componentCount; i++)
		{
			Position* nextPosition = positionManager->getComponentWithIndex(i);
			if (!nextPosition->isActive()) continue;
			SDL_RenderDrawPoint(renderer, nextPosition->x() - camera.x, nextPosition->y() - camera.y);
		}
	}
}

/**
* @brief Debug function that visualizes the colliders.
*/
void RenderSystem::debugColliders() {
	if (debug) {
		size_t componentCount = colliderManager->getComponentCount();

		for (size_t i = 0; i < componentCount; i++)
		{

			Collider* nextCollider = colliderManager->getComponentWithIndex(i);

			if (!nextCollider->isActive()) continue;
			SDL_Rect* colliderRect = nextCollider->getColliderRect();
			SDL_Rect renderRect = { colliderRect->x-camera.x, colliderRect->y-camera.y,colliderRect->w, colliderRect->h };
			SDL_RenderDrawRect(renderer, &renderRect);
		}
	}
}

/**
* @brief Debug functrion that visualizes the enemy pathing.
*/
void RenderSystem::debugEnemyPathing() {
	if (debug) {
		size_t componentCount = enemyMovementManager->getComponentCount();
		unsigned w = (unsigned)(this->getTileWidth()*this->cameraZoomX);
		unsigned h = (unsigned)(this->getTileHeight()*this->cameraZoomY);

		Node* prev = nullptr;
		for (size_t i = 0; i < componentCount; i++)
		{
			EnemyMovement* component = enemyMovementManager->getComponentWithIndex(i);
			for (auto node : component->getRoute()) {
				if (prev != nullptr) {
					SDL_RenderDrawLine(renderer, (prev->x * w + (w/2))-camera.x, (prev->y * h + (h/2))-camera.y, (node->x * w + (w / 2))-camera.x, (node->y * h + (h / 2))-camera.y);
				}
				prev = node;
			}
			prev = nullptr;
		}
	}
}

#pragma region UI
/**
* @brief Renders all the ui elements in the window.
*/
void RenderSystem::renderUI(){
	renderPanels();
	renderButtons();
	renderProgressBars();
	renderSliders();
	renderLabels();
}

/**
* @brief Renders all the labels of the ui.
*/
void RenderSystem::renderLabels() {
	size_t labelCount = uiManager->getCurrentLabelIndex();
	for (size_t i = 0; i < labelCount; i++) {
		Label* nextLabel = uiManager->getLabel(i);
		if (nextLabel->isVisible()) {
			SDL_RenderCopy(renderer, nextLabel->getLabelTexture(), NULL, nextLabel->getDisplayPosition());
		}
	}
}

/**
* @brief Renders all the panels of the ui.
*/
void RenderSystem::renderPanels() {
	size_t panelCount = uiManager->getCurrentPanelIndex();
	for (size_t i = 0; i < panelCount; i++) {
		Panel* nextPanel = uiManager->getPanel(i);
		if (nextPanel->isVisible()) {
			SDL_RenderCopy(renderer, nextPanel->getPanelTexture(), NULL, nextPanel->getDisplayPosition());
		}
	}
}

/**
* @brief Renders all the progress bars of the ui.
*/
void RenderSystem::renderProgressBars(){
	size_t progressBarCount = uiManager->getCurrentProgressBarIndex();
	for (size_t i = 0; i < progressBarCount; i++) {
		ProgressBar* nextProgressBar = uiManager->getProgressBar(i);
		if (nextProgressBar->isVisible()) {
			SDL_RenderCopy(renderer, nextProgressBar->getBackgroundTexture(), NULL, nextProgressBar->getBackgroundPosition());
			SDL_RenderCopy(renderer, nextProgressBar->getProgressTexture(), NULL, nextProgressBar->getProgressPosition());
		}
	}
}

/**
* @brief Renders all the sliders of the ui.
*/
void RenderSystem::renderSliders() {
	size_t sliderCount = uiManager->getCurrentSliderIndex();
	for (size_t i = 0; i < sliderCount; i++)
	{
		Slider* nextSlider = uiManager->getSlider(i);
		if (nextSlider->isVisible()) {
			SDL_RenderCopy(renderer, nextSlider->getBackgroundPanelTexture(), NULL, nextSlider->getBackgroundPosition());
			SDL_RenderCopy(renderer, nextSlider->getSliderKnobPanelTexture(), NULL, nextSlider->getSliderKnobPosition());
		}
	}
}

/**
* @brief Renders all the buttons of the ui.
*/
void RenderSystem::renderButtons() {
	size_t buttonCount = uiManager->getCurrentButtonIndex();
	for (size_t i = 0; i < buttonCount; i++) {
		Button* nextButton = uiManager->getButton(i);
		if (nextButton->isVisible()) {
			SDL_RenderCopy(renderer, nextButton->getButtonPanel(), NULL, nextButton->getButtonPanelPosition());
			SDL_RenderCopy(renderer, nextButton->getButtonText(), NULL, nextButton->getButtonTextPosition());
		}
	}
}
#pragma endregion UI

#pragma region Sprites
/**
* @brief Renders all current sprites in the window.
*/
void RenderSystem::renderSprites() {
	// sort sprites to display depth in 2d environment
	sortSprites();

	size_t index = spriteManager->getComponentCount();
	for (size_t i = 0; i < index; i++)
	{
		Position* spritePosition = &sortedSpritePositions[i];
		Entity spriteEntity = spritePosition->getEntity();
		Sprite* sprite = spriteManager->getComponent(spriteEntity);
		sprite->setDestinationRectPosition((spritePosition->x() - (sprite->getDestinationWidth()*cameraZoomX/ 2)) - camera.x, (spritePosition->y() - (sprite->getDestinationHeight()*cameraZoomY / 2)) - camera.y);
		draw(sprite);
	}
}

/**
* @brief Sorts the sprite before rendering. Needed to be able to display depth in 2d environment.
*/
void RenderSystem::sortSprites() {
	// copy current array
	size_t counter = 0;
	size_t componentCount = positionManager->getComponentCount();
	if (componentCount != 0) {
		for (size_t i = 0; i < componentCount; i++) {
			Position* pos = positionManager->getComponentWithIndex(i);
			if (spriteManager->hasComponent(pos->getEntity())) {
				sortedSpritePositions[counter] = *(positionManager->getComponentWithIndex(i));
				counter++;
			}
		}

		// sort array
		if (counter > 0) {
			mergeSort(&sortedSpritePositions[0], 0, counter - 1);
		}
	}
}

/**
 * @brief Sorts and merges the two parts of the position array together.
 * @param arr - array to sort and merge the two parts of.
 * @param start - Startindex of left side.
 * @param middle - Middleindex between left and right side.
 * @param end - Endindex of right side.
*/
void RenderSystem::merge(Position* arr, size_t start, size_t middle, size_t end) {
	size_t i, j, k;
	i = start;
	k = start;
	j = middle + 1;

	while (i <= middle && j <= end) {
		Sprite* leftSprite = spriteManager->getComponent(arr[i].getEntity());
		Sprite* rightSprite = spriteManager->getComponent(arr[j].getEntity());

		int leftY = arr[i].y() - (leftSprite->getDestinationHeight() / 2);
		int rightY = arr[j].y() - (rightSprite->getDestinationHeight() / 2);

		if (leftY < rightY) {
			this->sortArr[k] = arr[i];
			i++;
			k++;
		}
		else {
			this->sortArr[k] = arr[j];
			j++;
			k++;
		}
	}

	while (i <= middle) {
		this->sortArr[k] = arr[i];
		i++;
		k++;
	}

	while (j <= end) {
		this->sortArr[k] = arr[j];
		j++;
		k++;
	}

	for (i = start; i < k; i++) {
		arr[i] = this->sortArr[i];
	}
}

/**
 * @brief Merge sort implementation to sort an positions array.
 * @param arr - Positions array to sort.
 * @param start - Startindex of array.
 * @param end - Endindex of array.
*/
void RenderSystem::mergeSort(Position* arr, size_t start, size_t end) {
	size_t middle;
	if (start < end) {
		// divide array and conquer
		middle = (start + end) / 2;
		mergeSort(arr, start, middle);
		mergeSort(arr, middle + 1, end);
		// merge arrays
		merge(arr, start, middle, end);
	}
}

/**
 * @brief Checks if the sprite has a texture and creates a texture if it has not. Afterwards adds the sprite to the renderer to render.
 * @param sprite
*/
void RenderSystem::draw(Sprite* sprite) {
	// check if sprite is active
	if (!sprite->isActive())return;

	// if sprite has no texture
	if (!sprite->hasTexture()) {

		// load texture
		Texture spriteTexture = FileLoader::loadTexture(sprite->texturePath, renderer);

		// set texture of sprite aswell as width and height of texture
		sprite->setTexture(spriteTexture);
	}

	// ignore sprites outside of camera when animating/rendering
	SDL_Rect* rect  = sprite->getDestinationRect();

	SDL_Rect newRect = { rect->x, rect->y, rect->w* cameraZoomX, rect->h * cameraZoomY };

	if ((newRect.x+newRect.w) < 0 || newRect.x > window.x || (newRect.y+newRect.h) < 0 || newRect.y > window.y) {
		return;
	}

	Animator* animator = animatorManager->getComponent(sprite->getEntity());

	if (animator != nullptr && animator->hasAnimation()) {
		animateSprite(sprite, animator);
	}

	SDL_RenderCopyEx(renderer, sprite->getTexture().texture, sprite->getSourceRect(), &newRect, NULL, NULL, sprite->getTextureFlip());
}
#pragma endregion Sprites

#pragma region Animations
/**
* @brief Animates the sprite.
* @param sprite - Sprite to animate.
* @param animator - Animator with animation data.
*/
void RenderSystem::animateSprite(Sprite* sprite, Animator* animator) {
	int newX, newY;

	Animation* currentAnimation = animator->getCurrentAnimation();

	if (currentAnimation == nullptr) {
		return;
	}

	if (currentAnimation->hasAnimationTexture()) {
		Texture newTexture = currentAnimation->getAnimationTexture();
		sprite->setTexture(newTexture);
	}
	int currentFrame = 0;

	// check if the current animation is interruptible or should be played fully.
	if (currentAnimation->interruptible) {
		currentFrame = static_cast<int>((SDL_GetTicks() / currentAnimation->frameDelayMS) % currentAnimation->frames);
	}
	else {
		currentFrame = currentAnimation->currentFrame / (currentAnimation->frameDelayMS / this->frameDelay);
	}

	// increment current frame count
	currentAnimation->currentFrame = currentAnimation->currentFrame + 1;


	int lastTileInRow = sprite->getTexture().textureWidth - sprite->getSourceWidth();
	int currentTile = currentFrame * sprite->getSourceWidth();

	// Reset y offset when returning first frame of animation
	if (currentFrame == 0 && currentAnimation->interruptible) {
		currentAnimation->resetYOffset();
	}

	if (!currentAnimation->interruptible && currentFrame == currentAnimation->frames) {
		currentAnimation->setFinished();
		currentAnimation->resetYOffset();
	}

	// increase y offset if next row
	if (currentTile - lastTileInRow == sprite->getSourceWidth()) {
		currentAnimation->incrementYOffset(currentFrame);
	}

	// calc new x position on new row
	if ((currentTile) > (lastTileInRow)) {
		newX = (currentTile - lastTileInRow) - sprite->getSourceWidth();
	}
	else {
		newX = sprite->getSourceWidth() * currentFrame;
	}
	// calc new y position depending on offset
	newY = currentAnimation->getYOffset() * sprite->getSourceHeight();

	// set new area of sprite to display
	sprite->setSourceRectPosition(newX, newY);
}
#pragma endregion Animations

#pragma region Tilemap
/**
* @brief Sets the current tilemap to display.
* @param tilesetPath - Path to tileset image used by tilemap.
* @param tilemapPath - Path to tilemap json file generated by tiled.
* @param layerCount - Count of layers in tilemap.
* @return Pointer to created tilemap.
*/
Tilemap* RenderSystem::setMap(const char* tilesetPath, const char* tilemapPath, size_t layerCount) {
	SDL_Point size = { 0,0 };
	tilemap = FileLoader::loadTilemap(tilemapPath, layerCount);

	Texture tilesetTexture = FileLoader::loadTexture(tilesetPath, renderer);

	tileset = new Tileset(tilesetTexture);

	// set srcRect
	tileset->initSourceRect(tilemap->getTileWidth(), tilemap->getTileHeight());

	// set destRect
	tileset->initDestinationRect(tilemap->getTileWidth(), tilemap->getTileHeight());

	return this->tilemap;
}

/**
* @brief Renders the tilemap.
*/
void RenderSystem::renderTilemap() {
	if (this->tilemap == nullptr || this->tileset == nullptr) {
		return;
	}
	unsigned int currentDestX = 0;
	unsigned int currentDestY = 0;
	unsigned int maxTilesPerRow = tilemap->getTilesPerRow();
	unsigned int tileWidth = tilemap->getTileWidth();
	unsigned int tileHeight = tilemap->getTileHeight();
	size_t layers = tilemap->getLayerCount();
	int collisionLayer = tilemap->getCollisionLayerIndex();
	int objectLayer = tilemap->getTilemapObjectLayerIndex();

	for (size_t i = 0; i < layers; i++)
	{
		if (i == collisionLayer || i == objectLayer) {
			continue;
		}
		currentDestX = 0;
		currentDestY = 0;
		std::vector<unsigned int> layer = tilemap->getLayer(i);
		for (size_t i = 0; i < layer.size(); i++)
		{
			// checks if current x-position is greater or equals to max tilecount in row
			if (currentDestX >= maxTilesPerRow) {
				currentDestX = 0;
				currentDestY = currentDestY + 1;
			}
			// check if spot is empty
			if (layer[i] != 0) {
				// calculate part to render
				setTilesetSrcRectPosition(layer[i], tileWidth, tileHeight);

				// calculate part to render at ingame
				setTilesetDestRectPosition(currentDestX, currentDestY, tileWidth, tileHeight);

				SDL_Rect* rect = tileset->getDestinationRect();
				SDL_Rect newRect = { rect->x, rect->y, rect->w*cameraZoomX, rect->h*cameraZoomY };
				
				if ((newRect.x + newRect.w) < 0 || newRect.x > window.x || (newRect.y + newRect.h) < 0 || newRect.y > window.y) {
					// skip rendering
				}
				else {
					// if tile is in camera view, render tile.
					SDL_RenderCopy(renderer, tileset->getTexture().texture, tileset->getSourceRect(), &newRect);
				} 
			}
			currentDestX = currentDestX + 1;
		}
	}
}

/**
* @brief Sets the source rectangle of the tileset to display the right part of the tileset. It is important that the size of the tileset is a multiple of the tilesize.
* @param tilemapData - What tile to display based on the tilemap.
* @param tileWidth - Width of the tiles.
* @param tileHeight - Height of the tiles.
*/
void RenderSystem::setTilesetSrcRectPosition(unsigned int tilemapData, unsigned int tileWidth, unsigned int tileHeight) {
	unsigned int tilesetWidth = tileset->getTexture().textureWidth;

	int newX;
	int newY;
	// check if first row tileWidth * maxWidth
	if ((tilemapData * tileWidth) <= (tilesetWidth)) {
		newX = (tilemapData == 0) ? tilemapData * tileWidth : (tilemapData - 1) * tileWidth;
		newY = 0;
	}
	else {
		// calculate row
		unsigned int yoffset = (tilemapData * tileWidth) / (tilesetWidth);
		unsigned int xoffset = ((tilemapData * tileWidth) % (tilesetWidth)) / tileWidth;

		newX = (xoffset == 0) ? xoffset * tileWidth : (xoffset - 1) * tileWidth;
		newY = yoffset * tileHeight;
	}
	// set source rect position
	tileset->setSourceRect(newX, newY);
}

/**
* @brief Sets the destination rectangle of the tileset to display the tiles in the right area.
* @param currentX - Current X position on the tilemap.
* @param currentY - Current Y position on the tilemap.
* @param tileWidth - Width of the tiles.
* @param tileHeight - Height of the tiles.
*/
void RenderSystem::setTilesetDestRectPosition(unsigned int currentX, unsigned int currentY, unsigned int tileWidth, unsigned int tileHeight) {
	int newX;
	int newY;

	newX = currentX * (tileWidth*cameraZoomX);
	newY = currentY * (tileHeight*cameraZoomY);

	// substracts the calculated tile position based on tilewidth & the position on the tilemap from the camera origin position (top-left).
	// if the result is positiv, render the tile on the substracted position (relative to the camera origin).
	// if the result is negativ, don't render the tile.
	newX = newX - camera.x;
	newY = newY - camera.y;

	tileset->setDestinationRect(newX, newY);
}
#pragma endregion Tilemap

#pragma region Camera
/**
* @brief Initializes the camera with certain viewport.
* @param viewWidth - Width of viewport.
* @param viewHeight - Height of viewport.
* @param cameraWidth - Width of camera.
* @param cameraHeight - Height of camera.
*/
void RenderSystem::initCamera(int viewWidth, int viewHeight, int cameraWidth, int cameraHeight) {
	camera = { 0, 0,cameraWidth,cameraHeight };

	cameraZoomX = (float)viewWidth / cameraWidth;
	cameraZoomY = (float)viewHeight / cameraHeight;

	window = { viewWidth, viewHeight };
}

/**
 * @brief Moves the camera to the entity with the follow camera component.
*/
void RenderSystem::moveCamera() {
	// TODO: test with different maps and different view sizes
	if (cameraFollow != nullptr && cameraFollow->getEntity().uid != 0) {
		Entity followTarget = cameraFollow->getEntity();
		Position* followPosition = positionManager->getComponent(followTarget);

		camera.x = followPosition->x() - (window.x / 2);
		camera.y = followPosition->y() - (window.y / 2);

		//camera map bounds
		if (this->tilemap != nullptr) {
			// check the camera bounds
			// top-left
			if (camera.x < 0) {
				camera.x = 0;
			}
			if (camera.y < 0) {
				camera.y = 0;
			}

			//TODO: adjust camera movement for smoother movement. Update 19.12.21: gone?
			//bottom-right
			if (camera.x > (int)(tilemap->getTotalTilemapWidth()*cameraZoomX - window.x)) {
				camera.x = tilemap->getTotalTilemapWidth()*cameraZoomX - window.x;
			}

			if (camera.y > (int)(tilemap->getTotalTilemapHeight() * cameraZoomY - window.y)) {
				camera.y = tilemap->getTotalTilemapHeight() * cameraZoomY - window.y;
			}
		}
	}
}
#pragma endregion Camera