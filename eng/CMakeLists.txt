add_library(Engine STATIC
    # src/application.cpp
    src/implementation/window.cpp
    # src/ecs.cpp
)

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