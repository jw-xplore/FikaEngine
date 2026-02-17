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

    float getAspect() { return (float)width / (float)height; }

private:
    GLFWwindow* handle;
    int width = 0;
    int height = 0;
};