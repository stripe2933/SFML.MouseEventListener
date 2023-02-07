project(SFML_MouseEventListenerSample_Shapes)

add_executable(SFML_MouseEventListenerSample_Shapes
        main.cpp)

target_link_libraries(SFML_MouseEventListenerSample_Shapes
        PUBLIC SFML_MouseEventListener)

# Copy asset files to build directory.
# Copyright: https://stackoverflow.com/questions/42476765/copying-assets-directory-from-source-to-build-directory-in-cmake

add_custom_target(copy_assets
        COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_LIST_DIR}/copy-assets.cmake
        )
add_dependencies(SFML_MouseEventListenerSample_Shapes copy_assets)