#include "maze.h"
#include "loader.h"

namespace maze {
  void Maze::LoadMaze(const std::string& path) {
    MazeLoader loader(path);
    loader.ReadWalls(v_walls_, h_walls_);
  }

  std::size_t Maze::Size() const noexcept {
    return v_walls_.size();
  }

  const std::vector<std::vector<bool>>& Maze::GetV() const noexcept {
    return v_walls_;
  }

  const std::vector<std::vector<bool>>& Maze::GetH() const noexcept {
    return h_walls_;
  }

}
