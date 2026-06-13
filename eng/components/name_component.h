#pragma once
#include <string>
#include <ecs/ecs_component.h>


class NameComponent : public ECS_COMPONENT {
public:
    REGISTER_TYPE(NameComponent)
    NameComponent(const std::string& _name) : name(_name) {}
    std::string name;

    toml::table serialize() const override {
        toml::table t;
        t.insert("name", name);
        return t;
    }
};