
add_executable(Hepo_Editor
    main.cpp
)



target_link_libraries(Hepo_Editor
    PRIVATE 
        Engine
        imgui
)