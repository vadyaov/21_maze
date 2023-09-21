#include "maze.h"
#include "loader.h"

namespace maze {
  Maze::Maze(const std::string& path) {
    MazeLoader loader(path);
    loader.ReadWalls(v_walls_, h_walls_);
  }
}
