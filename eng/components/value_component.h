#pragma once
#include <string>
#include <ecs/ecs_component.h>


class ValueComponent : public ECS_COMPONENT {
public:
    REGISTER_TYPE(ValueComponent)
    ValueComponent(int _value) : value(_value) {}
    int value;
};