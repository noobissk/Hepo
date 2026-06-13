#pragma once

#include <cstdint>
#include <vector>
#include <unordered_map>
#include <typeindex>
#include <memory>
#include <string>

#include "istorage.h"
#include "ecs_entity.h"
#include "ecs_storage.h"


class Scene
{
public:
    Scene(const char _name[]) {
        name = _name;
    }

    std::string name;

    template<typename Component>
    Component* getComponent(Entity e)
    {
        auto it = components.find(std::type_index(typeid(Component)));

        if (it == components.end())
            return nullptr;

        return dynamic_cast<ECS_STORAGE<Component>*>(it->second.get())->get(e);
    }

    template<typename Component>
    void addComponent(Entity e, const Component& component)
    {
        auto type = std::type_index(typeid(Component));

        auto it = components.find(type);

        if (it == components.end())
        {
            auto storage = std::make_unique<ECS_STORAGE<Component>>();

            storage->add(e, component);

            components.emplace(type, std::move(storage));
        }
        else
        {
            auto* storage =
                dynamic_cast<ECS_STORAGE<Component>*>(it->second.get());

            if (storage)
            {
                storage->add(e, component);
            }
        }
    }

    template<typename Component>
    void removeComponent(Entity e)
    {
        auto it = components.find(std::type_index(typeid(Component)));

        if (it != components.end())
        {
            it->second->remove(e);
        }
    }

    template<typename Component>
    bool hasComponent(Entity e)
    {
        auto it = components.find(std::type_index(typeid(Component)));

        return it != components.end() &&
            it->second->has(e);
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

    std::unordered_map<std::type_index, std::unique_ptr<IStorage>> components;
private:


    // Entity management
    std::vector<uint32_t> generations;
    std::vector<uint32_t> free_ids;
};