#pragma once
struct GLFWwindow;

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
    float getAspect() { return (float)width / (float)height; }
    GLFWwindow* getHandle() { return handle; }

private:
    GLFWwindow* handle;
    int width = 0;
    int height = 0;
};