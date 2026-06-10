#pragma once
#include <GLFW/glfw3.h>

class AppWindow {
public:
    AppWindow() : window_resolution({800, 600}) {}
    AppWindow(int width, int height) : window_resolution({width, height}) {}
    ~AppWindow();

    bool open();
    void frameStart(); // single frame logic
    void frameLogic();
    void frameEnd();
    void close();

    // bool shouldClose();

    void throwError(int value);

    struct {
        int x, y;
    } window_resolution, window_position;

    bool checkFullscreen();
    void setFullscreen(bool value);
    GLFWwindow* window;
    GLFWmonitor* monitor;
private:

    void setGLFWWindowHints();

    bool is_fullscreen = false;
};

