#pragma once

#include "ecs/ecs_scene.h"

inline Scene& getCurrentScene() {
    static Scene scene("default scene");
    return scene;
}