#include "fikaEngine.h"
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
    CameraManager* cameraManager = SystemsHolder::getCameraManager();
    //cameraManager->useFreeCamera(true);

    //cameraManager->getFreeCamera()->lookAt(glm::vec3(0, 0, 1));
    //editor.loadProject();
	//editor.runGame();
}

void update(float dt)
{
    Renderer* debugRender = SystemsHolder::getDebugRenderer();
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