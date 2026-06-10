cmake_minimum_required(VERSION 3.28.3)
project(hepo VERSION 0.1.0)

option(BUILD_APP "build app exec" ON)
option(BUILD_EDITOR "build editor exec" ON)
option(BUILD_TOOLS "build tools exec" OFF)

find_package(glfw3 REQUIRED)
add_subdirectory(eng)
add_subdirectory(dependencies/glad)


if(BUILD_APP)
    add_subdirectory(app)
endif()

if(BUILD_EDITOR)
    add_subdirectory(edt/dependencies/imgui)
    add_subdirectory(edt)
endif()

if(BUILD_TOOLS)
    add_subdirectory(tools)
endif()
