#include "controller.h"

namespace maze {

  void Controller::ReadMaze(const std::string& path) {
    m.LoadMaze(path);
  }

  std::size_t Controller::Size() const noexcept {
    return m.Size();
  }

  const std::vector<std::vector<bool>>& Controller::GetVerticalWalls() const noexcept {
    return m.GetV();
  }

  const std::vector<std::vector<bool>>& Controller::GetHorizontalWalls() const noexcept {
    return m.GetH();
  }

}
