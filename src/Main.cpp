#include "SDL.h"
#include "entitymanager.h"
#include "componentmanager.h"
#include "components/components.h"
#include "systems/rendersystem.h"
#include "systems/physicsystem.h"
#include "inputmanager.h"

int main(int argc, char* argv[]) {
	int framerate = 60;
	float frameDelay = (float)(1000 / framerate);

	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow("Testwindow", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

	// TODO: Singleton Desingpattern for all managers and systems
	EntityManager* entityManager = new EntityManager();
	InputManager* inputManager = new InputManager();
	ComponentManager<Sprite>* spriteManager = new ComponentManager<Sprite>();
	ComponentManager<Position>* posManager = new ComponentManager<Position>();
	ComponentManager<Movement>* movementManager = new ComponentManager<Movement>();
	// TODO: special manager for single components in scene
	ComponentManager<CameraFollow>* cameraFollowManager = new ComponentManager<CameraFollow>();
	ComponentManager<Animator>* animatorManager = new ComponentManager<Animator>();

	RenderSystem* renderSystem = new RenderSystem(spriteManager, posManager, renderer, cameraFollowManager, animatorManager);
	renderSystem->setMap("../TestTextures/test_level_1.png", "../TestTextures/test_level_1.json", 2);
	// camera matches viewport
	renderSystem->initCamera(800, 600);
	PhysicSystem* physicSystem = new PhysicSystem(inputManager, movementManager, posManager);

	Entity entity = entityManager->createEntity();

	Sprite* spriteComponent = spriteManager->addComponent(entity);
	spriteComponent->setEntity(entity);
	spriteComponent->init("../TestTextures/char_idle.png", 64, 64, 1.5f);
	//spriteComponent->init("../TestTextures/char_atk_side.png", 64, 64, 1.5f);
	//spriteComponent->init("../TestTextures/char_walk.png", 64, 64, 1.5f);

	Position* positionComponent = posManager->addComponent(entity);
	positionComponent->setEntity(entity);
	positionComponent->x = 250;
	positionComponent->y = 250;

	Movement* movementComponent = movementManager->addComponent(entity);
	movementComponent->setEntity(entity);
	movementComponent->setMovementSpeed(5);

	// camera follow target = player
	CameraFollow* cameraFollow = cameraFollowManager->addComponent(entity);
	cameraFollow->setEntity(entity);

	Animator* animator = animatorManager->addComponent(entity);
	animator->addAnimation("idle", 5, 100);
	animator->addAnimation("attack", 3, 500, FileLoader::loadTexture("../TestTextures/char_atk_side.png", renderer));
	//animator->addAnimation("idle", 6, 100);
	//animator->play("idle");
	animator->play("attack");
	while (!inputManager->interrupted)
	{
		Uint32 startTimestamp = SDL_GetTicks();

		inputManager->update();
		if (inputManager->interrupted) break;

		physicSystem->update();
		renderSystem->update();

		Uint32 endTimestamp = SDL_GetTicks();
		Uint32 delay = frameDelay - (endTimestamp - startTimestamp);
		SDL_Delay(delay);
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
