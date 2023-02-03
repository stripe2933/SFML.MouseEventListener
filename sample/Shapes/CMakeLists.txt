project(SFML_MouseEventListenerSample_Shapes)

add_executable(SFML_MouseEventListenerSample_Shapes
        main.cpp)

target_link_libraries(SFML_MouseEventListenerSample_Shapes
        PUBLIC SFML_MouseEventListener)