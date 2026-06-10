#pragma once
#include <cstdint>

using Entity = uint64_t;

class IStorage {
public:
    virtual ~IStorage() = default;
    virtual void remove(Entity e) = 0;
};