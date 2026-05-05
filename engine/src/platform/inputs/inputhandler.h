#pragma once
#include "inputdevices.h"

struct GLFWwindow;

namespace Input
{
    class InputHandler
    {
        InputHandler() = delete;
        ~InputHandler() = delete;
    public:
        static void Init(GLFWwindow* window);
        // call before handling input
        static void BeginFrame();

        static void OnGLKeyCallback(GLFWwindow* win, int key, int scancode, int action, int mods);
        static void OnGLMousePressCallback(GLFWwindow* win, int button, int action, int mods);
        static void OnGLMouseMoveCallback(GLFWwindow* win, double x, double y);
        static void OnGLMouseScrollCallback(GLFWwindow* win, double x, double y);

        static void HandleKeyEvent(int key, int scancode, int action, int mods);
        static void HandleMousePressEvent(int button, int pressed, int mods);
        static void HandleMouseMoveEvent(double x, double y);
    };

    Keyboard* GetDefaultKeyboard();
    Mouse* GetDefaultMouse();

}