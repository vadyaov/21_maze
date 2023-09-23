#include "loader.h"

maze::MazeLoader::MazeLoader(const std::string& path) : istrm_{path}, sz_{0} {
  if (!istrm_.is_open())
    throw std::invalid_argument("Incorrect path.");

  int rows, columns;
  istrm_ >> rows >> columns;

  if (rows != columns || rows > 50 || rows < 2)
    throw std::invalid_argument("Incorrect size.");

  sz_ = rows;
}

void maze::MazeLoader::ReadWalls(wall_vector& vertical, wall_vector& horizontal) {
  ReadSingleArray(vertical);
  ReadSingleArray(horizontal);
}

void maze::MazeLoader::ReadSingleArray(wall_vector& arr) {
  int value;
  arr.resize(sz_);
  for (int i = 0; i < sz_; ++i) {
    arr[i].resize(sz_);
    for (int j = 0; j < sz_; ++j) {
      istrm_ >> value;
      arr[i][j] = value;
    }
  }
}
