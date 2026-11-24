# Fika Engine

## Links
- [YouTube](https://www.youtube.com/@FikaEngine) 

## Overview
Fika Engine is a C++ game engine that serves mainly as a experimental and educational project. The goal is to expand authors knowledge about game engines development and share this knowleged with others.

Project is work in progress and all parts can be significantly changed in future. 

## Features
- [ECS support](https://github.com/jw-xplore/FikaEngine/tree/main/engine/src/core/ecs) 
- [OpenGL renderer](https://github.com/jw-xplore/FikaEngine/tree/main/engine/src/renderer)
- [Simple shape collisions](https://github.com/jw-xplore/FikaEngine/tree/main/engine/src/physics)
- [Input Manager](https://github.com/jw-xplore/FikaEngine/tree/main/engine/src/platform/inputs)
- [Level Editor](https://github.com/jw-xplore/FikaEngine/tree/main/editor/src)
- [Audio Manager](https://github.com/jw-xplore/FikaEngine/tree/main/engine/src/audio)

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
5. Run cmd "createproj.bat projectName" in root folder.
6. Set custom project as start up project in VS.
7. Running the program should display black window with FPS counter.