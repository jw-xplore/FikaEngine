# Fika Engine
![logo](doc/logo.png)

## Overview
Fika Engine is a C++ game engine that serves mainly as a experimental and educational project. The goal is to expand authors knowledge about game engines development and shared this knowleged with others.

Project is work in progress and all parts can be significantly changed in future. 

## Using the engine
Currently engine is set to be used as a single Visual Studio solution.

Needs:
- Visual Studio (using 17)
- CMake (using 4.3.3)

Steps:
1. Download or clone source code.
2. Run externalpull.bat in root folder to download dependencies.
3. Run build.bat in root folder to build the solution.
4. Open FikaEngine.sln in build folder.
5. Run createproj.bat projectName in root folder
6. Set custom project as start up project in VS
7. Running the program should display black window with FPS counter

## TODO:
- Physics comments: Standardize and comment physics and collisions code

## Backlog
- Memory: Review pool allocator code and adjust with error handlig (pool overflow)
- Debug: Add custom debug console running inside game
- Debug memory - Allocations-dealocations debug log
- Physics memory: Utilize pool for bodies and colliders
- Physics: Rotation freeze implementation
- Multithreading: Test separated update and render threads
- Multithreading: Physics on separated thread
- Controls: Add controls contexts (so free cam controls can surpress player controls)
- UI: Create more general purpouse utility for imgui
- Use: Create setup for library style of use so engine with all externals can be reused inside other solutions