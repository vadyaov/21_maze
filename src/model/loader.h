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

      MazeLoader(const std::string& path);

      void ReadWalls(wall_vector& vertical, wall_vector& horizontal);

    private:
      std::ifstream istrm_;
      int sz_;

      void ReadSingleArray(wall_vector& arr);
  };
} // namespace maze

#endif // LOADER_H_
