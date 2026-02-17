#include "window.h"
#include <GLFW/glfw3.h>

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

    handle = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!handle) {
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(handle);

    // Enable vsync (prevents tearing)
    glfwSwapInterval(1);

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