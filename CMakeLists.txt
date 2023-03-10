cmake_minimum_required(VERSION 3.24)
project(SFML_MouseEventListener)

set(CMAKE_CXX_STANDARD 11)

add_library(SFML_MouseEventListener
        lib/ObjectBoundary.cpp include/ObjectBoundary.hpp
        lib/CircleBoundary.cpp include/CircleBoundary.hpp
        lib/AARectangleBoundary.cpp include/AARectangleBoundary.hpp
        lib/MouseEventListener.cpp include/MouseEventListener.hpp
        lib/MouseEventSystem.cpp include/MouseEventSystem.hpp
        lib/ConvexBoundary.cpp include/ConvexBoundary.hpp
        lib/GroupBoundary.cpp include/GroupBoundary.hpp)
target_include_directories(SFML_MouseEventListener
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

find_package(SFML COMPONENTS Graphics REQUIRED)

target_link_libraries(SFML_MouseEventListener
        PUBLIC SFML::Graphics)

add_subdirectory(sample)