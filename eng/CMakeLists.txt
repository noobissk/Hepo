add_library(Engine STATIC
    # src/application.cpp
    src/implementation/window.cpp
    # src/ecs.cpp
)

include(FetchContent)

FetchContent_Declare(
    tomlplusplus
    GIT_REPOSITORY https://github.com/marzer/tomlplusplus.git
    GIT_TAG v3.4.0
)

FetchContent_MakeAvailable(tomlplusplus)

target_link_libraries(Engine PRIVATE tomlplusplus::tomlplusplus)

target_link_libraries(Engine
    PUBLIC
        glfw
        glad
)



target_include_directories(Engine
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/components
    ${CMAKE_CURRENT_SOURCE_DIR}/misc
)