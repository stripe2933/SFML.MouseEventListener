project(SFML_MouseEventListenerSample_ManyConvexes)

add_executable(SFML_MouseEventListenerSample_ManyConvexes
        main.cpp DragObserver.hpp)
target_include_directories(SFML_MouseEventListenerSample_ManyConvexes
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(SFML_MouseEventListenerSample_ManyConvexes
        PUBLIC SFML_MouseEventListener)