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
    model/maze/Maze.h model/maze/Ceil.h model/maze/Maze.cc
    model/maze/MazeLoader.h model/maze/MazeLoader.cc
    model/BaseLoader.h

    model/cave/Cave.h model/cave/Cave.cc
    model/cave/CaveLoader.h

    view/main.cc
    view/MainWindow.h
    view/BaseRender.h
    view/maze/MazeRenderArea.cc view/maze/MazeRenderArea_utils.cc view/maze/MazeRenderArea.h
    view/cave/CaveRenderArea.cc view/cave/CaveRenderArea.h

    view/maze/MazeWindow.cc view/maze/MazeWindow.h
    view/cave/CaveWindow.cc view/cave/CaveWindow.h

    view/other/button.cc view/other/button.h

    controller/MazeController.cc controller/MazeController.h
    controller/CaveController.cc controller/CaveController.h
)

target_link_libraries(maze PUBLIC Qt::Widgets)
