#pragma once
#include <functional>

class Application {
private:
    void setup();

public:
    Application(void (*startFnc)(), void (*updateFnc)(float));
    ~Application();

    void (*startFnc)();
    void (*updateFnc)(float);
    void run();
};