cmake_minimum_required(VERSION 3.28)
project(interpreter)

set(CMAKE_CXX_STANDARD 14)

file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "include/*.h")

add_executable(interpreter ${SOURCES} ${HEADERS})