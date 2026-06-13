#pragma once
#include <string>
#include <toml++/toml.h>
#define REGISTER_TYPE(name) \
public: \
    const char* typeName() const override { return #name; }

class ECS_COMPONENT {
public:
    virtual toml::table serialize() const = 0;
    virtual const char* typeName() const = 0;
};