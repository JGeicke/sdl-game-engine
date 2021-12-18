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
	*/
	void init(int fps, std::string windowTitle, int windowWidth, int windowHeight);

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
	 * @brief Sets the current tilemap.
	 * @param tilesetFilePath - File path to the used tileset.
	 * @param tilemapDataFilePath - File path to the data of the tilemap.
	 * @param layerCount - Number of layers in the tilemap.
	*/
	void setTilemap(const char* tilesetFilePath, const char* tilemapDataFilePath, size_t layerCount);

	/**
	 * @brief Sets the current background music.
	 * @param bgmFilePath - File path to the background music.
	*/
	void setBGM(const char* bgmFilePath);

	/**
	 * @brief Changes current scene.
	 * @param scene - Scene to change to.
	*/
	void changeScene(Scene* scene);

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
	 * @param direction - Movement direction of the projectile.
	 * @param projectileSpeed - Projectile speed.
	 * @return Pointer to the added projectile movement component.
	*/
	ProjectileMovement* addProjectileMovement(Entity e, Vector2 direction, unsigned int projectileSpeed);

	/**
	 * @brief Gets position component of the entity.
	 * @param e - Entity to get component off.
	 * @return Pointer to the position component of the entity.
	*/
	Position* getPositionComponent(Entity e);

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
	 * @brief Loads scene.
	 * @param scene - Scene to load.
	*/
	void loadScene(Scene* scene);
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
	HealthSystem* healthSystem = nullptr;

	// Component managers
	ComponentManager<Sprite>* spriteManager =  nullptr;
	ComponentManager<Position>* posManager = nullptr;
	ComponentManager<Animator>* animatorManager = nullptr;
	ComponentManager<Audio>* audioManager = nullptr;
	ComponentManager<Collider>* colliderManager = nullptr;
	ComponentManager<Health>* healthManager = nullptr;
	ComponentManager<ProjectileMovement>* projectileMovementManager = nullptr;

	// Unique components
	CameraFollow* cameraFollow = nullptr;
	Movement* playerMovement = nullptr;

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
	 * @brief Initializes the game systems.
	*/
	void initSystems();

	/**
	 * @brief Collects and frees the entities and component that should not be preserved when switching scenes.
	*/
	void collectSceneGarbage();

	/**
	* @brief Resets last collisions of colliders when swapping scenes.
	*/
	void resetLastCollisions();

	/**
	 * @brief Removes components of entity.
	*/
	void removeEntityComponents(Entity e);
};