cmake_minimum_required(VERSION 3.28)
project(interpreter)

set(CMAKE_CXX_STANDARD 14)

file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "include/*.h")

add_executable(interpreter ${SOURCES} ${HEADERS})

# Add Google Test to the project
add_subdirectory(cmake-build-debug/googletest)

# Test target
file(GLOB_RECURSE TESTS "test/*.cpp")
add_executable(interpreter_test ${TESTS} src/calculator.cpp src/token.cpp)

# Link Google Test to the test target
target_link_libraries(interpreter_test gtest_main)