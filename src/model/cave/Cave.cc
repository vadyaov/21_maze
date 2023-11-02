#include "Cave.h"

#include <random>
#include <cmath>

namespace cave {

  void Cave::LoadCave(const std::string& path) {
    CaveLoader loader;
    loader.OpenFile(path);
    ceils_ = loader.ReadCave();
  }

  std::size_t Cave::Size() const noexcept {
    return std::sqrt(ceils_.size());
  }

  bool Cave::At(int row, int col) const {
    return ceils_.at(row * Size() + col);
  }

  void Cave::Init(int size, double probability) {
    ceils_.resize(size * size);

    std::random_device rd;
    std::mt19937 engine(rd());
    std::uniform_real_distribution<double> normal_distrib(0.0, 1.0);

    for (int i = 0; i < size * size; ++i) {
      double random_value = normal_distrib(engine);
      if (random_value <= probability)
        ceils_[i] = true;
      else
        ceils_[i] = false;
    }

  }

  void Cave::NextGeneration(int life_lim, int death_lim) {
    std::vector<bool> next = ceils_;

    for (std::size_t i = 0; i < Size(); ++i)
      for (std::size_t j = 0; j < Size(); ++j) {
        int alive_num = CountAliveAround(i, j);

        if (At(i, j) == false) {
          if (alive_num <= death_lim)
            next[i * Size() + j] = true;
        } else {
          if (alive_num > life_lim + 1)
            next[i * Size() + j] = false;
        }
      }

    ceils_ = next;

  }

  int Cave::CountAliveAround(std::size_t i, std::size_t j) const {
    int num = 0;

    /* left */
    if (j != 0 && At(i, j - 1) == false) {
      ++num;
    }

    /* left top */
    if (j != 0 && i != 0 && At(i - 1, j - 1) == false) {
      ++num;
    }

    /* top */
    if (i != 0 && At(i - 1, j) == false) {
      ++num;
    }

    /* right top */
    if (j != Size() - 1 && i != 0 && At(i - 1, j + 1) == false) {
      ++num;
    }

    /* right */
    if (j != Size() - 1 && At(i, j + 1) == false) {
      ++num;
    }

    /* right bot */
    if (j != Size() - 1 && i != Size() - 1 && At(i + 1, j + 1) == false) {
      ++num;
    }

    /* bot */
    if (i != Size() - 1 && At(i + 1, j) == false) {
      ++num;
    }

    /* left bot */
    if (i != Size() - 1 && j != 0 && At(i + 1, j - 1) == false) {
      ++num;
    }

    return num;
  }

} // namespace cave
