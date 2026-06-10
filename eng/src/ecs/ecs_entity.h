#pragma once
#include <cstdint>


using Entity = uint64_t;

constexpr uint32_t EntityId(Entity e) {
    return static_cast<uint32_t>(e);
}

constexpr uint32_t EntityGeneration(Entity e) {
    return static_cast<uint32_t>(e >> 32);
}

constexpr Entity MakeEntity(uint32_t id, uint32_t generation) {
    return (static_cast<uint64_t>(generation) << 32) | id;
}