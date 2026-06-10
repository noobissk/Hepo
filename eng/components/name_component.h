#pragma once
#include <string>


class NameComponent {
public:
    NameComponent(const std::string& _name) : name(_name) {}
    std::string name;
};