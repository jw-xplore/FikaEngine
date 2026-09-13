#pragma once
/**
* @author Based on inputserver.h from Nebula: https://github.com/gscept/nebula.git
*/
#include "input_devices.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class InputManager
{
public:
    InputManager();
	~InputManager();

    void init(GLFWwindow* window);
    /**
     * @brief Call at the frame start. Restarts state of input devices like key pressed, held, etc.
     */
    void beginFrame();

    Keyboard& getKeyboard();
    Mouse& getMouse();

    bool isKeyPressed(Key::Code key);
    bool isKeyReleased(Key::Code key);
    bool isKeyHeld(Key::Code key);

    bool isMousePressed(Mouse::Button button);
    bool isMouseReleased(Mouse::Button button);
    bool isMouseHeld(Mouse::Button button);
    glm::vec2 mousePosition();
    double mouseScroll();

private:
    // GL callbacks
    static void onGLKeyCallback(GLFWwindow* win, int key, int scancode, int action, int mods);
    static void onGLMousePressCallback(GLFWwindow* win, int button, int action, int mods);
    static void onGLMouseMoveCallback(GLFWwindow* win, double x, double y);
    static void onGLMouseScrollCallback(GLFWwindow* win, double x, double y);

    static void handleKeyEvent(int key, int scancode, int action, int mods);
    static void handleMousePressEvent(int button, int pressedKeys, int mods);
    static void handleMouseMoveEvent(double x, double y);
};