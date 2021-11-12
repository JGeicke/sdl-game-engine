#include "SDL.h"
#include "entitymanager.h"
#include "componentmanager.h"
#include "components/components.h"
#include "systems/rendersystem.h"
#include "systems/physicsystem.h"
#include "inputmanager.h"

int main(int argc, char* argv[]) {
	/*
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window *window = SDL_CreateWindow("Testwindow", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

	SDL_RenderClear(renderer);

	SDL_RenderPresent(renderer);

	SDL_Delay(3000);
	EntityManager *entityManager = new EntityManager();
	Entity e = entityManager->createEntity();
	entityManager->createEntity();
	entityManager->debugListEntities();
	entityManager->destroyEntity(e);
	entityManager->debugListEntities();
	// BASE
	EntityManager* entityManager = new EntityManager();
	Entity ent = entityManager->createEntity();
	Entity ent2 = entityManager->createEntity();

	// Check Entites
	std::cout << "UID:" << ent.uid << "\n";
	std::cout << "UID:" << ent2.uid << "\n";

	// Component Manager
	ComponentManager<Position>* posManager = new ComponentManager<Position>();

	// Testing
	posManager->addComponent(ent);
	Position* p = posManager->getComponent(ent);
	p->x = 23;
	p->y = 36;
	p->print(); // expected: (23,36)

	Position* ex = posManager->getComponent(ent);
	ex->print(); // expected: (23,36)

	posManager->addComponent(ent2);
	Position* ent2p = posManager->getComponent(ent2);
	ent2p->x = 42;
	ent2p->print(); // expected: (42,0)

	posManager->DebugListEntityIndexMap();

	posManager->removeComponent(ent);

	posManager->DebugListEntityIndexMap();
	*/
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
	ComponentManager<CameraFollow>* cameraFollowManager = new ComponentManager<CameraFollow>();

	RenderSystem* renderSystem = new RenderSystem(spriteManager, posManager, renderer, cameraFollowManager);
	renderSystem->setMap("../TestTextures/test_level_1.png", "../TestTextures/test_level_1.json", 2);
	PhysicSystem* physicSystem = new PhysicSystem(inputManager, movementManager, posManager);

	Entity entity = entityManager->createEntity();

	Sprite* spriteComponent = spriteManager->addComponent(entity);
	spriteComponent->setEntity(entity);
	spriteComponent->init("../TestTextures/shroom.png", 32, 32, 1.5f);

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
