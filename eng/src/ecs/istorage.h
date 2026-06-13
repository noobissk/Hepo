#pragma once
#include <cstdint>
#include <ostream>
#include <string>
#include <toml++/toml.h>

using Entity = uint64_t;

class IStorage {
public:
    virtual ~IStorage() = default;
    virtual void remove(Entity e) = 0;
    virtual bool has(Entity e) const = 0;
    virtual const char* componentTypeName() const = 0;
    virtual toml::array serialize() const = 0;
};