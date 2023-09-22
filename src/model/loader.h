#ifndef LOADER_H_
#define LOADER_H_

#include <iostream>

#include <string>
#include <vector>
#include <fstream>

namespace maze {
  class MazeLoader {
    public:

      using wall_vector = std::vector<std::vector<bool>>;

      /* MazeLoader() = delete; */
      MazeLoader(const std::string& path) : istrm_{path}, sz_{0} {
        if (!istrm_.is_open())
          throw std::invalid_argument("Incorrect path.");

        int rows, columns;
        istrm_ >> rows >> columns;

        if (rows != columns || rows > 50)
          throw std::invalid_argument("Incorrect size.");

        sz_ = rows;
      }

      void ReadWalls(wall_vector& vertical, wall_vector& horizontal) {
        ReadSingleArray(vertical);
        ReadSingleArray(horizontal);
      }

    private:
      std::ifstream istrm_;
      int sz_;

      void ReadSingleArray(wall_vector& arr) {
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
  };
} // namespace s21

#endif // LOADER_H_
