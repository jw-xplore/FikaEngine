#include "window.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "inputs/inputhandler.h"

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

bool Window::create(int width, int height, const char* title)
{
    this->width = width;
    this->height = height;

    if (!glfwInit()) return false;

    //glfwWindowHint(GLFW_VERSION_MAJOR, 3);
    //glfwWindowHint(GLFW_VERSION_MINOR, 5);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    handle = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!handle) {
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(handle);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD\n";
        return false;
    }

    // Enable vsync (prevents tearing)
    glfwSwapInterval(1);

    Input::InputHandler::Init(handle);

    return true;
}

void Window::poll()
{
    glfwPollEvents();
    glfwSetKeyCallback(handle, key_callback);
}

void Window::swap()
{
    glfwSwapBuffers(handle);
}

bool Window::shouldClose() const
{
    return glfwWindowShouldClose(handle);
}

void Window::destroy()
{
    glfwDestroyWindow(handle);
    glfwTerminate();
}