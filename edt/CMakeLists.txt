
add_executable(Hepo_Editor
    main.cpp
)

FetchContent_Declare(
    tomlplusplus
    GIT_REPOSITORY https://github.com/marzer/tomlplusplus.git
    GIT_TAG v3.4.0
)

FetchContent_MakeAvailable(tomlplusplus)

target_link_libraries(Hepo_Editor PRIVATE tomlplusplus::tomlplusplus)

target_link_libraries(Hepo_Editor
    PRIVATE 
        Engine
        imgui
)