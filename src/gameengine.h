#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "entitymanager.h"
#include "componentmanager.h"
#include "components/components.h"
#include "systems/gamesystems.h"
#include "inputmanager.h"
#include "uimanager.h"
#include "util/window.h"
/**
 * @brief Game Engine class. Used to initialize systems and managers aswell as start the gameloop.
*/
class GameEngine{
public:
	GameEngine() {

	}

	~GameEngine() {
	}

	void init(int fps, std::string windowTitle, int windowWidth, int windowHeight);

	void run();

	void quit();

	Entity addEntity(SDL_Point position);

	void setCameraFollowTarget(Entity e);

	void resetCameraFollowTarget();

	Entity addPlayer(SDL_Point position, unsigned int movementSpeed);

	void setTilemap(const char* tilesetFilePath, const char* tilemapDataFilePath, size_t layerCount);

	void setBGM(const char* bgmFilePath);

	Sprite* addSpriteComponent(Entity e, const char* filePath, SDL_Point size, float scale);

	Collider* addColliderComponent(Entity e, SDL_Point offset, SDL_Point size, bool isTrigger);

	Audio* addAudioComponent(Entity e);

	size_t addAudioClip(Entity e, const char* filePath);

	Animator* addAnimatorComponent(Entity e);

	void addAnimation(Entity e, size_t animationState, int frames, int frameDelayMS, const char* filePath);

	void addAnimation(Entity e, size_t animationState, int frames, int frameDelayMS);

	Position* getPositionComponent(Entity e);

	Sprite* getSpriteComponent(Entity e);

	Collider* getColliderComponent(Entity e);

	Audio* getAudioComponent(Entity e);

	Animator* getAnimatorComponent(Entity e);

	Movement* getPlayerMovementComponent(Entity e);

	InputManager* getInputManager() { return inputManager; }

	UIManager* getUIManager() { return uiManager; }

	ComponentManager<Sprite>* getSpriteManager(){return spriteManager;}

	ComponentManager<Position>* getPositionManager(){return posManager;}

	ComponentManager<Animator>* getAnimatorManager(){return animatorManager;}

	ComponentManager<Audio>* getAudioManager(){return audioManager;}

	ComponentManager<Collider>* getColliderManager() {return colliderManager;}
private:
	int frameDelay = 1000 / 60;

	Window* window = nullptr;
	
	// Managers
	EntityManager* entityManager = nullptr;
	InputManager* inputManager = nullptr;
	UIManager* uiManager = nullptr;
	// Systems
	RenderSystem* renderSystem = nullptr;
	PhysicSystem* physicSystem = nullptr;
	AudioSystem* audioSystem = nullptr;

	// Component managers
	ComponentManager<Sprite>* spriteManager =  nullptr;
	ComponentManager<Position>* posManager = nullptr;
	ComponentManager<Animator>* animatorManager = nullptr;
	ComponentManager<Audio>* audioManager = nullptr;
	ComponentManager<Collider>* colliderManager = nullptr;

	// Unique components
	CameraFollow* cameraFollow = nullptr;
	Movement* playerMovement = nullptr;

	void initManagers();
	void initComponentManagers();
	void initUniqueComponents();
	void initSystems();
};