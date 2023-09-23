#include "loader.h"

namespace maze {
  MazeLoader::MazeLoader(const std::string& path) : istrm_{path}, sz_{0} {
    if (!istrm_.is_open())
      throw std::invalid_argument("Incorrect path.");

    int rows, columns;
    istrm_ >> rows >> columns;

    if (rows != columns || rows > 50 || rows < 2)
      throw std::invalid_argument("Incorrect size.");

    sz_ = rows;
  }

  void MazeLoader::ReadWalls(std::vector<Ceil>& ceils) {
    int value;
    ceils.resize(sz_ * sz_);
    for (std::size_t i = 0; i < ceils.size(); ++i) {
        istrm_ >> value;
        ceils[i].GetRight() = value;
    }

    for (std::size_t i = 0; i < ceils.size(); ++i) {
        istrm_ >> value;
        ceils[i].GetDown() = value;
    }
  }

} // namespace maze
