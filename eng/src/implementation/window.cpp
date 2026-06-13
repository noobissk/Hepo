#include <iostream>
#include <glad.h>
#include "../window.h"

void sizeCallback(GLFWwindow* window, int width, int height)
{
    auto* app =
        static_cast<AppWindow*>(glfwGetWindowUserPointer(window));

    if (!app->checkFullscreen())
    {
        app->window_resolution.x = width;
        app->window_resolution.y = height;
    }
}

bool AppWindow::open() {
    monitor = glfwGetPrimaryMonitor();
    setGLFWWindowHints();

    window = glfwCreateWindow(800, 600, "OpenGL Window", NULL, NULL);
    if (!window) {
        return false;
    }

    glfwMakeContextCurrent(window);

    // if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    // {
    //     std::cout << "Failed to initialize GLAD\n";
    //     return false;
    // }
    glfwSetWindowSizeCallback(window, sizeCallback);
    glfwSetWindowUserPointer(window, this);
    glfwMakeContextCurrent(window); // Initial context binding
    
    // IMPORTANT: If sharing resources, pass a shared context in glfwCreateWindow
    // glfwCreateWindow(..., sharedContextWindow);
    return true;
}

void AppWindow::frameStart() {
    glfwMakeContextCurrent(window);

    glClear(GL_COLOR_BUFFER_BIT);

    // ecsSystem.render(); 
}
void AppWindow::frameLogic() {
    if (glfwGetWindowAttrib(window, GLFW_FOCUSED) == GLFW_FALSE) 
        return;

    static bool a = false;
    if (glfwGetKey(window, GLFW_KEY_F11) == GLFW_PRESS && !a) {
        setFullscreen(!checkFullscreen());
        a = true;
    } else if (glfwGetKey(window, GLFW_KEY_F11) != GLFW_PRESS) {
        a = false;
    }
}
void AppWindow::frameEnd() {
    glfwSwapBuffers(window);
}

void AppWindow::close() {
    glfwSetWindowShouldClose(window, GLFW_TRUE);
    glClear(GL_COLOR_BUFFER_BIT);
    // glfwDestroyWindow(window);
}

AppWindow::~AppWindow()
{
    if (window)
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwDestroyWindow(window);
        window = nullptr;
    }
}

void AppWindow::throwError(int value) {
    std::cout << "[WINDOW ERROR] has occured with an output value of '" << value << "'\n";
}

bool AppWindow::checkFullscreen() {
    return is_fullscreen;
}

void AppWindow::setFullscreen(bool value) {
    if (value == checkFullscreen())
        return;

    if (value) {
        // --- Enter Fullscreen ---
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
        
        glfwGetWindowPos(window, &window_position.x, &window_position.y);
        // glfwGetWindowSize(window, &window_resolution.x, &window_resolution.y);
        
        glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
    } else {
        // --- Exit Fullscreen (Restore Windowed) ---
        glfwSetWindowMonitor(window, NULL, window_position.x, window_position.y, window_resolution.x, window_resolution.y, 0);
    }
    
    is_fullscreen = value;
    if (is_fullscreen)
        std::cout << "fullscreen -> on" << std::endl;
    else 
        std::cout << "fullscreen -> off" << std::endl;

}

bool is_fullscreen = false;


void AppWindow::setGLFWWindowHints() {
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);

    glfwWindowHint(GLFW_RED_BITS, mode->redBits);
    glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
    glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
    glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
}
