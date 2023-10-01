#include "cave.h"

namespace cave {

  void Cave::LoadCave(const std::string& path) {
    loader->OpenFile(path);
    ceils_ = loader->ReadCave();
  }

} // namespace cave
