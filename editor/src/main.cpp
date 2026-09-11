#include "fika_engine.h"
#include <fstream>
#include <string>
#include <iostream>
#include <windows.h>

#include "editor.h"

/**
 * @brief Fika Editor main
 */

FikaEditor::Editor editor;

void start()
{
    CameraManager* cameraManager = FikaServers::getCameraManager();
    //cameraManager->useFreeCamera(true);
    cameraManager->getMainCamera()->move(glm::vec3(0, 2, 6), glm::vec3(0,0,-1));

    //cameraManager->getFreeCamera()->lookAt(glm::vec3(0, 0, 1));
    //editor.loadProject();
	//editor.runGame();

    //editor.placeObject(glm::vec3(0, 0, 0));

    // TODO: Have engine components initilized at engine
    TransformComponentUpdater::init();
    RigidBodyComponentUpdater::init();
    MeshComponentUpdater::init();

    editor.loadProject();
}

void update(float dt)
{
    Renderer* debugRender = FikaServers::getDebugRenderer();
    glm::vec3 start = glm::vec3(0);

    debugRender->addLine(Line(start, start + glm::vec3(1, 0, 0), glm::vec3(1, 0, 0)));
    debugRender->addLine(Line(start, start + glm::vec3(0, 1, 0), glm::vec3(0, 1, 0)));
    debugRender->addLine(Line(start, start + glm::vec3(0, 0, 1), glm::vec3(0, 0, 1)));

    editor.update();
}

int main()
{
    FikaEngine::run(start, update);
}