cmake_minimum_required(VERSION 3.16)

project(21_maze VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 COMPONENTS Widgets)

add_compile_options(-Wall -Werror -Wextra -Wpedantic)
add_compile_options(-fsanitize=address)
add_link_options(-fsanitize=address)

qt_add_executable(maze
    model/maze.h model/maze.cc
    model/loader.h model/loader.cc

    view/main.cc
    view/mainwindow.h
    view/base_render.h
    view/mazerenderarea.cc view/mazerenderarea_utils.cc view/mazerenderarea.h
    view/window.cc view/window.h
    view/button.cc view/button.h
    view/label.cc view/label.h

    controller/controller.cc controller/controller.h
)

target_link_libraries(maze PUBLIC Qt::Widgets)
