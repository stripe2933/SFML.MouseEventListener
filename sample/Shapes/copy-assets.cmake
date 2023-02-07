# A CMake script for copying asset files to build directory.
# Copyright: https://stackoverflow.com/questions/42476765/copying-assets-directory-from-source-to-build-directory-in-cmake

file(COPY ${CMAKE_CURRENT_LIST_DIR}/assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
