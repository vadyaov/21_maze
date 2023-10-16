#include "CaveLoader.h"

namespace cave {

  std::vector<bool> CaveLoader::ReadCave() {
    int value;
    std::vector<bool> cave;
    cave.resize(sz_ * sz_);

    for (std::size_t i = 0; i < cave.size(); ++i) {
        istrm_ >> value;
        cave[i] = value;
    }

    CloseFile();

    return cave;
  }

} // namespace cave
