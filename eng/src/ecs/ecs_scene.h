#pragma once

#include <cstdint>
#include <vector>
#include <unordered_map>
#include <typeindex>
#include <memory>
#include <string>

#include "ecs_entity.h"
#include "ecs_storage.h"


class Scene
{
public:
    Scene(const char _name[]) {
        name = _name;
    }

    std::string name;

    template<typename T>
    ECS_STORAGE<T>& getStorage() {
        auto type = std::type_index(typeid(T));

        auto it = components.find(type);
        if (it == components.end()) {
            auto inserted = components.emplace(
                type,
                std::make_unique<ECS_STORAGE<T>>()
            );
            return *static_cast<ECS_STORAGE<T>*>(inserted.first->second.get());
        }

        return *static_cast<ECS_STORAGE<T>*>(it->second.get());
    }

    // Entity management
    Entity createEntity() {
        uint32_t id;
        if (!free_ids.empty()) {
            id = free_ids.back();
            free_ids.pop_back();
        } else {
            // add an int for next_id if adding allocator!!
            id = static_cast<uint32_t>(generations.size());
            generations.push_back(0);
        }
        return MakeEntity(id, generations[id]);
    }
    void destroyEntity(Entity e, bool delete_all_components) {
        uint32_t id = EntityId(e);

        generations[id]++;
        free_ids.push_back(id);

        if (delete_all_components)
            for (const auto&  [key, value] : components)
            {
                value->remove(e);
            }
    }

    bool isAlive(Entity e) {
        uint32_t id = EntityId(e);
        return id < generations.size() && id == EntityGeneration(e);
    }

private:
    std::unordered_map<std::type_index, std::unique_ptr<IStorage>> components;


    // Entity management
    std::vector<uint32_t> generations;
    std::vector<uint32_t> free_ids;
};