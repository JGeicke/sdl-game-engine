#include "SDL.h"
#include "entitymanager.h"
#include "componentmanager.h"
#include "components/position.h"

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
	*/
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
	return 0;
}
