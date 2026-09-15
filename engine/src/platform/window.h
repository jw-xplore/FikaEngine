#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

namespace FikaEngine
{
    class Window {
    public:
        //Window() {}

        bool create(int width, int height, const char* title);
        void poll();
        bool shouldClose() const;
        void swap();
        void destroy();

        float getWidth() { return width; }
        float getHeight() { return height; }
        const glm::vec2 getSize() { return glm::vec2(width, height); }
        float getAspect() { return (float)width / (float)height; }
        GLFWwindow* getHandle() { return handle; }

    private:
        GLFWwindow* handle;
        int width = 0;
        int height = 0;
    };
} // namespace FikaEngine
