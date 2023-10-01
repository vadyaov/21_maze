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
    model/maze/maze.h model/maze/ceil.h model/maze/maze.cc
    model/maze/mazeloader.h model/maze/mazeloader.cc
    model/BaseLoader.h

    view/main.cc
    view/mainwindow.h
    view/base_render.h
    view/maze/mazerenderarea.cc view/maze/mazerenderarea_utils.cc view/maze/mazerenderarea.h
    view/maze/mazewindow.cc view/maze/mazewindow.h
    view/redef_widgets/button.cc view/redef_widgets/button.h
    view/redef_widgets/label.cc view/redef_widgets/label.h

    controller/controller.cc controller/controller.h
)

target_link_libraries(maze PUBLIC Qt::Widgets)
