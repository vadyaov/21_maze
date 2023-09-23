#ifndef LOADER_H_
#define LOADER_H_

#include <iostream>

#include <string>
#include <fstream>

#include "maze.h"

namespace maze {
  class MazeLoader {
    public:

      MazeLoader(const std::string& path);

      void ReadWalls(std::vector<Ceil>& ceils);

    private:
      std::ifstream istrm_;
      int sz_;
  };
} // namespace maze

#endif // LOADER_H_
