cmake_minimum_required(VERSION 3.27)
project(Assignment4)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS_RELEASE "-Oz -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O0 -g")

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

add_executable(main main.cpp main-window.ui
        Graph.cpp
        Graph.h)

target_link_libraries(main PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Widgets
)