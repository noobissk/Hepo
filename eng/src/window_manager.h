#pragma once

#include <vector>
#include <memory>
#include <glad.h>
#include <algorithm>

#include <events.h>
#include "window.h"

class WindowManager {
private:
    inline static std::vector<std::unique_ptr<AppWindow>> windows;
    // ECSWorld& ecsWorld; // Reference to ECS
    
public:
    inline static Event<void(float)> on_update;

    inline static void init() {
        if (!glfwInit()) {
            std::cerr << "Failed to initialize GLFW\n";
            glfwTerminate();
            return;
        }
    }
    inline static AppWindow* addWindow() {
        auto newWin = std::make_unique<AppWindow>();
        if (newWin->open()) {
            if (windows.size() == 0) {
                std::cout << "initializing glad\n";
                if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
                    std::cout << "Failed to initialize GLAD\n";
                    return nullptr;
                }
            }
            windows.push_back(std::move(newWin));
            return windows.back().get();
        }
        return nullptr;
    }

    inline static void run() {
        while (!windows.empty()) {
            for (auto& win : windows)
                win->frameStart();

            // ecsWorld.updateSystems(0.016f); 
            float dt = 0.01f;
            on_update.invoke(dt);

            for (auto& win : windows)
                win->frameLogic();


            for (auto& win : windows)
                win->frameEnd();


            // Cleanup Closed Windows
            windows.erase(
                std::remove_if(windows.begin(), windows.end(),
                    [](const std::unique_ptr<AppWindow>& w) {
                        bool shouldClose = glfwWindowShouldClose(w->window);

                        if (shouldClose)
                            std::cout << "Removing window\n";

                        return shouldClose;
                    }),
                windows.end()
            );
            glfwPollEvents();
        }
        glfwTerminate();
    }
};