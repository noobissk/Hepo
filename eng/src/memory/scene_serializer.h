#pragma once
#include <toml++/toml.hpp>
#include <ecs/ecs_scene.h>
#include <ostream>
#include <istream>


class SceneSerializer {
public:
    inline static void saveScene(const Scene& scene) {
        std::ofstream stream (scene.name + ".toml");
        toml::table table;
        for (auto& [type, storage] : scene.components)
        {
            table.insert(storage.get()->componentTypeName(), storage->serialize()); // join them all into 1 toml
        }
        stream << table;
    }
};