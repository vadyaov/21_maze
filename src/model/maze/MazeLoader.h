#ifndef LOADER_H_
#define LOADER_H_

#include <vector>

#include "../BaseLoader.h"
#include "Ceil.h"

namespace maze {
  class MazeLoader : public BaseLoader {
    public:
      std::vector<Ceil> ReadMaze();
  };
} // namespace maze

#endif // LOADER_H_
