#include "CaveController.h"

namespace cave {

  void Controller::ReadCave(const std::string& path) {
    c.LoadCave(path);
  }

  std::size_t Controller::Size() const noexcept {
    return c.Size();
  }

  bool Controller::At(int i, int j) const {
    return c.At(i, j);
  }

  void Controller::MakeNextGen(int life, int death) {
    c.NextGeneration(life, death);
  }

  void Controller::InitializeCave(int size, double prob) {
    c.Init(size, prob);
  }


} // namespace cave
