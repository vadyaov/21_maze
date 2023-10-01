#include "MazeController.h"

namespace maze {

  void Controller::ReadMaze(const std::string& path) {
    m.LoadMaze(path);
  }

  void Controller::GenMaze(std::size_t size) {
    m.Generate(size);
  }

  std::vector<Maze::Coord> Controller::FindSolution(Maze::Coord first, Maze::Coord second) {
    return m.FindSolution(first, second);
  }

  std::size_t Controller::Size() const noexcept {
    return m.Size();
  }

  const std::vector<Ceil>& Controller::GetCeils() const & noexcept {
    return m.GetCeils();
  }

} // namespace maze
