cmake_minimum_required(VERSION 3.27)
project(Assignment4)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS_RELEASE "-Oz -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O0 -g")

find_package(Qt6)

add_executable(main main.cpp)
