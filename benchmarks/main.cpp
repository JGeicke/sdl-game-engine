#include "Timer.h"
#include <iostream>
#include <gameengine.h>
#include <Windows.h>
#include <stdio.h>
#include <psapi.h>


class Benchmarks {
public:
	static void testObjectPools(size_t iterations) {
		Entity arr[100];
		GameEngine* gameEngine = new GameEngine();
		Timer* a = new Timer();

		gameEngine->init(60, "Benchmark", 1280, 720, 1280, 720, "../demo/assets/DemoGame/icon.png", false);

		for (size_t n = 0; n < iterations; n++)
		{
			// create
			for (size_t i = 0; i < 100; i++)
			{
				arr[i] = gameEngine->createProjectile("../demo/assets/DemoGame/sprites/proj.png", { 6,6 }, 2.0f, { 0, 0 }, { 1,1 }, 5.0f, true);
			}

			// destroy
			for (size_t i = 0; i < 100; i++) {
				gameEngine->destroyProjectile(arr[i]);
			}
		}
		a->stop();
	}

	static void testManualCreation(size_t iterations) {
		Entity arr[100];
		GameEngine* gameEngine = new GameEngine();
		gameEngine->debugDisableObjectPools();
		Timer* a = new Timer();

		gameEngine->init(60, "Benchmark", 1280, 720, 1280, 720, "../demo/assets/DemoGame/icon.png", false);

		for (size_t n = 0; n < iterations; n++)
		{
			// create
			for (size_t i = 0; i < 100; i++)
			{
				arr[i] = gameEngine->addEntity("projectile", false, { 0, 0 });
				gameEngine->addSpriteComponent(arr[i], "../demo/assets/DemoGame/sprites/proj.png", { 6,6 }, 2.0f);
				Collider* projCollider = gameEngine->addColliderComponent(arr[i], { 0,0 }, { 12,12 }, true);
				gameEngine->addProjectileMovementComponent(arr[i], { 0,0 }, { 1, 1 }, 5.0f, true);
			}

			// destroy
			for (size_t i = 0; i < 100; i++) {
				gameEngine->destroyEntity(arr[i]);
			}
		}
		a->stop();
	}

	static void checkMaxComponentCount(size_t count) {
		GameEngine* gameEngine = new GameEngine();
		gameEngine->debugDisableObjectPools();
		gameEngine->init(60, "Benchmark", 1280, 720, 1280, 720, "../demo/assets/DemoGame/icon.png", false);

		for (size_t i = 0; i < count; i++)
		{
			// check component manager with positions
			gameEngine->addEntity("benchmark", false, { 0,0 });


		}
	}

	static void checkComponentMemory() {
		int div = 1048576;

		PROCESS_MEMORY_COUNTERS pmc;
		uint64_t usedRAMPostInit(0);
		uint64_t singleCreationRAM(0);
		uint64_t currentUsedRAM(0);


		GameEngine* gameEngine = new GameEngine();
		gameEngine->debugDisableObjectPools();
		gameEngine->init(60, "Benchmark", 1280, 720, 1280, 720, "../demo/assets/DemoGame/icon.png", false);

		BOOL result = GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
		usedRAMPostInit = pmc.WorkingSetSize;

		std::cout << "After init: " <<usedRAMPostInit <<  "Byte ("<< usedRAMPostInit / div <<"MB)" << "\n";


		for (size_t i = 0; i < 1; i++)
		{
			// check component manager with positions
			gameEngine->addEntity("benchmark", false, { 0,0 });


		}

		result = GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
		singleCreationRAM = pmc.WorkingSetSize - usedRAMPostInit;
		std::cout << "One Entity + component: " << singleCreationRAM << "Byte ("<< singleCreationRAM/div <<"MB)" << "\n";

		for (size_t i = 0; i < 999; i++)
		{
			// check component manager with positions
			gameEngine->addEntity("benchmark", false, { 0,0 });
		}

		result = GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
		currentUsedRAM = pmc.WorkingSetSize - usedRAMPostInit;
		std::cout << "100 Entity + component: " << currentUsedRAM << "Byte (" << currentUsedRAM / div << "MB)" << "\n";
		std::cout << currentUsedRAM / singleCreationRAM << "\n";
	}

};

int main(int argc, char* argv[]) {
	int n = 7500;

	/*
	std::cout << "n = " << n << "\n";
	std::cout << "+++++++++++++++++++++++++ Object Pools++++++++++++++++++++++++++++\n";
	Benchmarks::testObjectPools(n);
	std::cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
	std::cout << "+++++++++++++++++++++++++ Manual +++++++++++++++++++++++++++++++++\n";
	Benchmarks::testManualCreation(n);
	std::cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";

	Benchmarks::checkMaxComponentCount(1024);
	 */
	Benchmarks::checkComponentMemory();
	return 0;
}