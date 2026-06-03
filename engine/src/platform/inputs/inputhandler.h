#pragma once
/**
* @author Based on inputserver.h from Nebula: https://github.com/gscept/nebula.git 
*/
#include "inputdevices.h"
#include <iostream>

struct GLFWwindow;

namespace Input
{
    class InputHandler
    {
        InputHandler() = delete;
        ~InputHandler() = delete;
    public:
        static void init(GLFWwindow* window);
        // call before handling input
        static void beginFrame();

        static void onGLKeyCallback(GLFWwindow* win, int key, int scancode, int action, int mods);
        static void onGLMousePressCallback(GLFWwindow* win, int button, int action, int mods);
        static void onGLMouseMoveCallback(GLFWwindow* win, double x, double y);
        static void onGLMouseScrollCallback(GLFWwindow* win, double x, double y);

        static void handleKeyEvent(int key, int scancode, int action, int mods);
        static void handleMousePressEvent(int button, int pressed, int mods);
        static void handleMouseMoveEvent(double x, double y);
    };

    Keyboard* getDefaultKeyboard();
    Mouse* getDefaultMouse();

}