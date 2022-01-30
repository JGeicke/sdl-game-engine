# Simple SDL2 Engine
## About
---
Small 2D game engine with SDL2 library for roguelike games. It was created for my university bachelor project.

---
## Feature List
---
- Build as entity component system
- AABB collision detection with collider and triggers
- Pathfinding to target or position
- Music and Sound
- 5 UI elements
- Supports orthogonal maps created with [Tiled](https://www.mapeditor.org/) and exported to json
- 2D depth rendering
- Seperated window and 2d camera sizes
- Projectile movement towards mouse position
- Implemented object pools
- Objects/entities can be kept through cleanup by marking them


---
## Getting Started
---
Before compiling you need to install the following libraries:
- [SDL2](https://www.libsdl.org/)
- [SDL2 TTF](https://github.com/libsdl-org/SDL_ttf)
- [SDL2 Image](https://www.libsdl.org/projects/SDL_image/)
- [SDL2 Mixer](https://www.libsdl.org/projects/SDL_mixer/)


---
## About Tiled
---
[Tiled](https://www.mapeditor.org/) is a free 2D level editor to develop maps for your game. This engine supports orthogonal maps created with Tiled v1.7.2. The maps need to be exported into json files to be used by the engine. The tileset used by Tiled is not needed, only the image the tileset is based of.

By using **object layers** in Tiled, the engine can automatically create objects in the scene with the tilemap. The sprites used by the object are the tiles on the same position used on the next normal layer. If you name the object layer in your tilemap **"collision"**, you can add colliders automatically for walls, trees etc. directly when loading your tilemap. No need to create those colliders manually.
Only rectangles are supported on object layers.

---
## Demo Game
---

---
## Documentation
---
The code documentation can be found [here](https://jgeicke.github.io/).
