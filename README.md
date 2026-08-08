# Fika Engine

## Overview
Fika Engine is a C++ game engine that serves mainly as a experimental and educational project. The goal is to expand authors knowledge about game engines development and share this knowleged with others.

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
5. Run createproj.bat projectName in root folder.
6. Set custom project as start up project in VS.
7. Running the program should display black window with FPS counter.

## TODO:
- Collisions: Finnish capsule to box collision
- Collisions: Fix box collisions with uneven volume ratio
- Collisions: Add capsule to capsule handling
- Raycast: Spheres
- Raycast: Boxes
- Raycast: Capsules
- Physics comments: Comment physics and collisions code
- Debug memory: Allocations-dealocations debug log
- Debug: Implement way to turn on/off debug/log features 

## Backlog
- Debug: Add custom debug console running inside game
- Physics: Rotation freeze implementation
- GO manager: Use pool allocator for game objects
- Multithreading: Test separated update and render threads
- Multithreading: Physics on separated thread
- Controls: Add controls contexts (so free cam controls can surpress player controls)
- UI: Create more general purpouse utility for imgui
- Use: Create setup for library style of use so engine with all externals can be reused inside other solutions
- Guide: Add basic API use guide and examples
- Example: Create proper example project
- Window/camera: Add resizing support
- Collisions: Predict and stop objects from moving in and back between collision point