#ifndef CAVE_LOADER_H_
#define CAVE_LOADER_H_

#include "../BaseLoader.h"

class CaveLoader : public BaseLoader {
  public:
    std::vector<bool> ReadCave() {
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
};

#endif // CAVE_LOADER_H_
