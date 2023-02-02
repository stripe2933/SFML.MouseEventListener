project(SFML_MouseEventListenerSample)

add_executable(SFML_MouseEventListenerSample
        main.cpp DragObserver.hpp)
target_include_directories(SFML_MouseEventListenerSample PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(SFML_MouseEventListenerSample
        PUBLIC SFML_MouseEventListener)