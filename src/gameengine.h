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
#include "util/scene.h"
#include "util/objectpool.h"
#include <cmath>
/**
 * @brief Game Engine class. Used to initialize systems and managers aswell as start the gameloop.
*/
class GameEngine{
public:
	/**
	 * @brief Default constructor of game engine.
	*/
	GameEngine() {

	}

	/**
	* @brief Default destructor of game engine.
	*/
	~GameEngine() {
	}

	/**
	 * @brief Initializes the game engine.
	 * @param fps - Target frames per seconds of game loop.
	 * @param windowTitle - Title of game window.
	 * @param windowWidth - Width of game window.
	 * @param windowHeight - Height of game window.
	 * @param cameraWidth - Width of camera.
	 * @param cameraHeight - Height of camera.
	*/
	void init(int fps, std::string windowTitle, int windowWidth, int windowHeight, int cameraWidth, int cameraHeight);

	/**
	 * @brief Runs the game engine. Starts the game loop.
	*/
	void run();

	/**
	 * @brief Quits the game engine and used libraries.
	*/
	void quit();

	/**
	 * @brief Adds an entity.
	 * @param tag - Tag of entity
	 * @param isPreserved -  Whether the entity is preserved across scenes.
	 * @param position - Position of the entity.
	 * @return Added entity.
	*/
	Entity addEntity(const char* tag, bool isPreserved, SDL_Point position);

	/**
	 * @brief Destroys the entity and its component.
	 * @param e - Entity to destroy.
	*/
	void destroyEntity(Entity e);

	/**
	 * @brief Sets the entity that the camera follows.
	 * @param e - Entity to follow.
	*/
	void setCameraFollowTarget(Entity e);

	/**
	 * @brief Resets the entity that the camera follows.
	*/
	void resetCameraFollowTarget();

	/**
	 * @brief Adds player entity. The player entity acts like a regular entity but is moveable.
	 * @param tag - Tag of entity
	 * @param isPreserved -  Whether the entity is preserved across scenes.
	 * @param position - Position of the player entity.
	 * @param movementSpeed - Movement speed of the player entity.
	 * @return The player entity.
	*/
	Entity addPlayer(const char* tag, bool isPreserved, SDL_Point position, unsigned int movementSpeed);

	/**
	 * @brief Creates new projectile from projectile object pool.
	 * @param spritePath - File path to sprite.
	 * @param size - Size of sprite.
	 * @param scale - Scale of sprite.
	 * @param start  - Start position.
	 * @param target - Target position.
	 * @param projectileSpeed - Projectile speed.
	 * @param isCursorTarget - Whether the cursor position is the target position.
	 * @return Projectile entity.
	*/
	Entity createProjectile(const char* spritePath, SDL_Point size, float scale, SDL_Point start, SDL_Point target, float projectileSpeed, bool isCursorTarget);

	/**
	 * @brief Destroys projectile of projectile object pool.
	 * @param e - Entity to destroy.
	*/
	void destroyProjectile(Entity e);

	/**
	 * @brief Sets the current background music.
	 * @param bgmFilePath - File path to the background music.
	 * @param loopBGM - Whether bgm should be looped.
	*/
	void setBGM(const char* bgmFilePath, bool loopBGM);

	/**
	 * @brief Plays audio clip with index of entity.
	 * @param e - Entity to play audio clip of.
	 * @param index - Index of audio clip.
	*/
	void playAudioClip(Entity e, size_t index);

	/**
	 * @brief Plays audio file. This is needed for elements outside of the ecs to be able to use the audio system.
	 * @param path - Path to audio file.
	*/
	void playAudioFile(const char* path);

	/**
	 * @brief Sets the destination of the enemy.
	 * @param e - Entity to set the destination from.
	 * @param pos - Destination position.
	*/
	void setEnemyDestination(Entity e, Position* pos);

	/**
	 * @brief Changes current scene.
	 * @param scene - Scene to change to.
	 * @param collectEverything - Whether every Entity should be collected.
	 * @param loopBGM - Whether bgm should be looped
	*/
	void changeScene(Scene* scene, bool clearEveryEntity, bool loopBGM);

	/**
	 * @brief Adds a sprite component to the entity.
	 * @param e - Entity to add component to
	 * @param filePath - File path to the sprite file.
	 * @param size - SDL_Point(width, height) representing the texture size.
	 * @param scale - Scale of the texture.
	 * @return Pointer to the added sprite component.
	*/
	Sprite* addSpriteComponent(Entity e, const char* filePath, SDL_Point size, float scale);

	/**
	 * @brief Adds a sprite component to the entity with custom source rectangle.
	 * @param e - Entity to add component to
	 * @param filePath - File path to the sprite file.
	 * @param srcRectPosition - Start position of source rectangle.
	 * @param size - SDL_Point(width, height) representing the texture size.
	 * @param scale - Scale of the texture.
	 * @return Pointer to the added sprite component.
	*/
	Sprite* addSpriteComponent(Entity e, const char* filePath, SDL_Point srcRectPosition, SDL_Point size, float scale);

	/**
	 * @brief Adds a collider component to the entity.
	 * @param e - Entity to add component to
	 * @param offset - SDL_Point(XOffset, YOffset). Offset of the collider. Relative to the entities position.
	 * @param size - SDL_Point(width, height) representing the size of the collider.
	 * @param isTrigger - Whether the collider is a trigger.
	 * @return Pointer to the added collider component.
	*/
	Collider* addColliderComponent(Entity e, SDL_Point offset, SDL_Point size, bool isTrigger);

	/**
	 * @brief Adds an audio component to the entity.
	 * @param e - Entity to add component to.
	 * @return Pointer to the added audio component.
	*/
	Audio* addAudioComponent(Entity e);

	/**
	 * @brief Adds audio clip to entities audio component.
	 * @param e - Entity of the audio component.
	 * @param filePath - File path to the audio file.
	 * @return Index of the added audio clip.
	*/
	size_t addAudioClip(Entity e, const char* filePath);

	/**
	 * @brief Adds an animator component to the entity.
	 * @param e - Entity to add component to.
	 * @return Pointer to the added animator component.
	*/
	Animator* addAnimatorComponent(Entity e);

	/**
	 * @brief Adds animation to entites animator component.
	 * @param e - Entity of the animator component.
	 * @param animationState - Animation state that triggers the animation.
	 * @param frames - Number of frames in the animation.
	 * @param frameDelayMS - Delay between the frames in MS.
	 * @param filePath - File path to the animation texture.
	*/
	void addAnimation(Entity e, size_t animationState, int frames, int frameDelayMS, const char* filePath);

	/**
	 * @brief Adds animation to entites animator component.
	 * @param e - Entity of the animator component.
	 * @param animationState - Animation state that triggers the animation.
	 * @param frames - Number of frames in the animation.
	 * @param frameDelayMS - Delay between the frames in MS.
	*/
	void addAnimation(Entity e, size_t animationState, int frames, int frameDelayMS);

	/**
	 * @brief Adds a health component to the entity.
	 * @param e - Entity to add component to.
	 * @param maximumHealth - Maximum health value.
	 * @return Pointer to the added health component.
	*/
	Health* addHealthComponent(Entity e, int maximumHealth);

	/**
	 * @brief Adds a projectile movement component to the entity.
	 * @param e - Entity to add component to.
	 * @param start - Start position.
	 * @param target- Target position.
	 * @param projectileSpeed - Projectile speed.
	 * @param isCursorTarget - Whether the target position is the position of the mouse cursor in the window.
	 * @return Pointer to the added projectile movement component.
	*/
	ProjectileMovement* addProjectileMovementComponent(Entity e, SDL_Point start, SDL_Point target, float projectileSpeed, bool isCursorTarget);
	
	/**
	 * @brief Adds a enemy movement component to the entity.
	 * @param e - Entity to add component to.
	 * @param movementSpeed - Movement speed of the entity.
	 * @return Pointer to the added enemy movement component.
	*/
	EnemyMovement* addEnemyMovementComponent(Entity e, float movementSpeed);

	/**
	 * @brief Adds a enemy movement component to the entity.
	 * @param e - Entity to add component to.
	 * @param movementSpeed - Movement speed of the entity.
	 * @param pathfindingTimerMS - Timer how often the path is calculated.
	 * @return Pointer to the added enemy movement component.
	*/
	EnemyMovement* addEnemyMovementComponent(Entity e, float movementSpeed, int pathfindingTimerMS);

	/**
	 * @brief Adds a enemy movement component to the entity.
	 * @param e - Entity to add component to.
	 * @param movementSpeed - Movement speed of the entity.
	 * @param target - Target Entity.
	 * @return Pointer to the added enemy movement component.
	*/
	EnemyMovement* addEnemyMovementComponent(Entity e, float movementSpeed, Entity target);

	/**
	 * @brief Adds a enemy movement component to the entity.
	 * @param e - Entity to add component to.
	 * @param movementSpeed - Movement speed of the entity.
	 * @param pathfindingTimerMS - Timer how often the path is calculated.
	 * @param target - Target Entity.
	 * @return Pointer to the added enemy movement component.
	*/
	EnemyMovement* addEnemyMovementComponent(Entity e, float movementSpeed, int pathfindingTimerMS, Entity target);

	/**
	 * @brief Gets position component of the entity.
	 * @param e - Entity to get component off.
	 * @return Pointer to the position component of the entity.
	*/
	Position* getPositionComponent(Entity e);

	/**
	 * @brief Sets the position of the entity.
	 * @param e - Entity to set position of.
	 * @param pos - New position of entity.
	*/
	void setPosition(Entity e, SDL_Point pos);

	/**
	 * @brief Gets sprite component of the entity.
	 * @param e - Entity to get component off.
	 * @return Pointer to the sprite component of the entity.
	*/
	Sprite* getSpriteComponent(Entity e);

	/**
	 * @brief Gets collider component of the entity.
	 * @param e - Entity to get component off.
	 * @return Pointer to the collider component of the entity.
	*/
	Collider* getColliderComponent(Entity e);

	/**
	 * @brief Gets audio component of the entity.
	 * @param e - Entity to get component off.
	 * @return Pointer to the audio component of the entity.
	*/
	Audio* getAudioComponent(Entity e);

	/**
	 * @brief Gets animator component of the entity.
	 * @param e - Entity to get component off.
	 * @return Pointer to the animator component of the entity.
	*/
	Animator* getAnimatorComponent(Entity e);

	/**
	 * @brief Gets movement component of the player entity.
	 * @param e - Entity to get component off.
	 * @return Pointer to the movement component of the player entity.
	*/
	Movement* getPlayerMovementComponent(Entity e);

	/**
	 * @brief Gets health component of the entity.
	 * @param e - Entity to get component off.
	 * @return Pointer to the health component of the entity.
	*/
	Health* getHealthComponent(Entity e);

	/**
	 * @brief Gets enemy movement component of the entity.
	 * @param e - Entity to get component off.
	 * @return Pointer to the enemy movement component of the entity.
	*/
	EnemyMovement* getEnemyMovementComponent(Entity e);

	/**
	 * @brief Gets the input manager of the game engine.
	 * @return Pointer to the input manager of the game engine.
	*/
	InputManager* getInputManager() { return inputManager; }

	/**
	 * @brief Gets the ui manager of the game engine.
	 * @return Pointer to the ui manager of the game engine.
	*/
	UIManager* getUIManager() { return uiManager; }

	/**
	 * @brief Gets the sprite component manager of the game engine.
	 * @return Pointer to the sprite component manager of the game engine.
	*/
	ComponentManager<Sprite>* getSpriteManager(){return spriteManager;}

	/**
	 * @brief Gets the position component manager of the game engine.
	 * @return Pointer to the position component manager of the game engine.
	*/
	ComponentManager<Position>* getPositionManager(){return posManager;}

	/**
	 * @brief Gets the animator component manager of the game engine.
	 * @return Pointer to the animator component manager of the game engine.
	*/
	ComponentManager<Animator>* getAnimatorManager(){return animatorManager;}

	/**
	 * @brief Gets the audio component manager of the game engine.
	 * @return Pointer to the audio component manager of the game engine.
	*/
	ComponentManager<Audio>* getAudioManager(){return audioManager;}

	/**
	 * @brief Gets the collider component manager of the game engine.
	 * @return Pointer to the collider component manager of the game engine.
	*/
	ComponentManager<Collider>* getColliderManager() {return colliderManager;}

	/**
	 * @brief Gets the health component manager of the game engine.
	 * @return Pointer to the health component manager of the game engine.
	*/
	ComponentManager<Health>* getHealthManager() { return healthManager; }

	/**
	 * @brief Gets the projectile movement component manager of the game engine.
	 * @return Pointer to the projectile movement component manager of the game engine.
	*/
	ComponentManager<ProjectileMovement>* getProjectileMovementManager() { return projectileMovementManager; }

	/**
	 * @brief Gets the enemy movement component manager of the game engine.
	 * @return Pointer to the enemy movement component manager of the game engine.
	*/
	ComponentManager<EnemyMovement>* getEnemyMovementManager() { return enemyMovementManager; }

	/**
	 * @brief Gets game window width.
	 * @return Width of game window.
	*/
	unsigned int getGameWindowWidth() { return this->window->getWindowWidth(); }

	/**
	 * @brief Gets game window height.
	 * @return Height of game window.
	*/
	unsigned int getGameWindowHeight() { return this->window->getWindowHeight(); }

	/**
	 * @brief Gets the renderer of the current window.
	 * @return Pointer to the current SDL_Renderer.
	*/
	SDL_Renderer* getRenderer() {
		return this->window->getRenderer();
	}

	/**
	 * @brief Gets the camera x zoom factor.
	 * @return Camera x zoom factor.
	*/
	float getCameraZoomFactorX() {
		return this->renderSystem->getCameraZoomFactorX();
	}

	/**
	 * @brief Gets the camera y zoom factor.
	 * @return Camera y zoom factor.
	*/
	float getCameraZoomFactorY() {
		return this->renderSystem->getCameraZoomFactorY();
	}

	/**
	 * @brief Sets the master volume of the audio system.
	 * @param newMasterVolume - New master volume.
	*/
	void setMasterVolume(float newMasterVolume) {
		audioSystem->setMasterVolume(newMasterVolume);
	}

	/**
	 * @brief Sets the sound volume of the audio system.
	 * @param newSoundVolume - New sound volume.
	*/
	void setSoundVolume(float newSoundVolume) {
		audioSystem->setSoundVolume(newSoundVolume);
	}

	/**
	 * @brief Sets the music volume of the audio system.
	 * @param newMusicVolume - New music volume.
	*/
	void setMusicVolume(float newMusicVolume) {
		audioSystem->setMusicVolume(newMusicVolume);
	}

	/**
	 * @brief Gets the current master volume of the audio system.
	 * @return The current master volume.
	*/
	float getMasterVolume() { return audioSystem->getMasterVolume(); }

	/**
	 * @brief Gets the current music volume of the audio system.
	 * @return The current music volume.
	*/
	float getMusicVolume() { return audioSystem->getMusicVolume(); }

	/**
	 * @brief Gets the current sound volume of the audio system.
	 * @return The current sound volume.
	*/
	float getSoundVolume() { return audioSystem->getSoundVolume(); }
private:
	/**
	 * @brief Delay between frames.
	*/
	int frameDelay = 1000 / 60;

	/**
	 * @brief Pointer to the game window.
	*/
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
	ComponentManager<Health>* healthManager = nullptr;
	ComponentManager<ProjectileMovement>* projectileMovementManager = nullptr;
	ComponentManager<EnemyMovement>* enemyMovementManager = nullptr;

	// Unique components
	CameraFollow* cameraFollow = nullptr;
	Movement* playerMovement = nullptr;

	//Object pool
	ObjectPool* projectilePool = nullptr;

	/**
	 * @brief Initializes the managers of the game engine.
	*/
	void initManagers();

	/**
	 * @brief Initializes the component manager of the game engine.
	*/
	void initComponentManagers();
	/**
	 * @brief Initializes the unique components of the game engine.
	*/
	void initUniqueComponents();

	/**
	 * @brief Initializes the object pools.
	*/
	void initObjectPools();
	/**
	 * @brief Initializes the game systems.
	 * @param cameraWidth - Width of camera.
	 * @param cameraHeight - Height of camera.
	*/
	void initSystems(int cameraWidth, int cameraHeight);

	/**
	 * @brief Collects and frees the entities and component that should not be preserved when switching scenes.
	 * @param collectEverything - Whether every Entity should be collected.
	*/
	void collectSceneGarbage(bool collectEverything);

	/**
	 * @brief Collects objects of the object pools.
	*/
	void collectObjects();

	/**
	 * @brief Collects objects of the projectile object pool.
	*/
	void collectProjectileObjects();

	/**
	* @brief Resets last collisions of colliders when swapping scenes.
	*/
	void resetLastCollisions();

	/**
	 * @brief Sets the current tilemap.
	 * @param tilesetFilePath - File path to the used tileset.
	 * @param tilemapDataFilePath - File path to the data of the tilemap.
	 * @param layerCount - Number of layers in the tilemap.
	*/
	void setTilemap(const char* tilesetFilePath, const char* tilemapDataFilePath, size_t layerCount);

	/**
	 * @brief Removes components of entity.
	*/
	void removeEntityComponents(Entity e);

	/**
	 * @brief Calculates the angle of the vector a->b in the unit circle.
	 * @param a - Point a
	 * @param b - Point b
	 * @return Angle of vector a->b
	*/
	double calcAngle(SDL_Point a, SDL_Point b);

	/**
	 * @brief Loads scene.
	 * @param scene - Scene to load.
	 * @param loopBGM - Whether bgm should be looped.
	*/
	void loadScene(Scene* scene, bool loopBGM);
};