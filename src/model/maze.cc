#include "maze.h"
#include "loader.h"

namespace maze {
  void Maze::LoadMaze(const std::string& path) {
    MazeLoader loader(path);
    loader.ReadWalls(ceils_);
  }

  void Maze::Generate(std::size_t size) {

    std::cout << size << std::endl;
  }

  std::size_t Maze::Size() const noexcept {
    return ceils_.size();
  }

  const std::vector<Ceil>& Maze::GetCeils() const & noexcept {
    return ceils_;
  }

}
