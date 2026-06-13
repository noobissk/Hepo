#pragma once
#include <vector>
#include <unordered_map>
#include <cstdint>

#include "ecs_entity.h"
#include "ecs_component.h"

using Entity = uint64_t;

template<typename T>
class ECS_STORAGE : public IStorage{
public:
    ECS_STORAGE () = default;

    std::vector<T> dense_components;
    std::vector<Entity> dense_entities;
    std::vector<size_t> sparse;


    const char* componentTypeName() const override {
        return dense_components[0].typeName();
    }

    toml::array serialize() const {
        toml::array arr;

        for (Entity e : dense_entities)
        {
            toml::table t = get(e)->serialize();
            t.insert("entityId", EntityId(e));

            arr.push_back(std::move(t));
        }

        return arr;
    }

    void add(Entity e, const T& component) {
        uint32_t id = EntityId(e);

        // ensure sparse is always large enough
        if (id >= sparse.size())
            sparse.resize(id + 1, SIZE_MAX);
        
        // if exists, overwrite
        if (sparse[id] != SIZE_MAX) {
            dense_components[sparse[id]] = component;
            return;
        }

        // insert new
        size_t dense_id = dense_components.size();
        dense_components.push_back(component);
        dense_entities.push_back(e);

        sparse[id] = dense_id;
    }

    

    T* get(Entity e) {
        if (!has(e))
            return nullptr;

        uint32_t id = EntityId(e);

        return &dense_components[sparse[id]];
    }

    const T* get(Entity e) const {
        if (!has(e))
            return nullptr;

        uint32_t id = EntityId(e);

        return &dense_components[sparse[id]];
    }

    void remove(Entity e) override
    {
        uint32_t id = EntityId(e);

        size_t dense_id = sparse[id];
        if (dense_id == SIZE_MAX) return;

        size_t last = dense_components.size() - 1;

        dense_components[dense_id] = dense_components[last];
        dense_entities[dense_id] = dense_entities[last];

        sparse[EntityId(dense_entities[dense_id])] = dense_id;

        dense_components.pop_back();
        dense_entities.pop_back();

        sparse[id] = SIZE_MAX;
    }

    bool has(Entity e) const override
    {
        uint32_t id = EntityId(e);

        if (id >= sparse.size())
            return false;

        size_t dense_id = sparse[id];

        return dense_id != SIZE_MAX &&
            dense_id < dense_entities.size() &&
            dense_entities[dense_id] == e;
    }

private:

};