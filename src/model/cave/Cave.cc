#include "Cave.h"

#include <iostream>
#include <random>

namespace cave {

  void Cave::LoadCave(const std::string& path) {
    CaveLoader loader;
    loader.OpenFile(path);
    ceils_ = loader.ReadCave();
  }

  void Cave::Init(int size, double probability) {
    ceils_.resize(size * size);

    std::random_device rd;
    std::mt19937 engine(rd());
    std::uniform_real_distribution<double> normal_distrib(0.0, 1.0);

    for (int i = 0; i < size * size; ++i) {
      double random_value = normal_distrib(engine);
      if (random_value <= probability)
        ceils_[i] = false;
      else
        ceils_[i] = true;
    }

  }

  void Cave::NextGeneration(int life_lim, int death_lim) {
    std::vector<bool> next = ceils_;

    for (std::size_t i = 0; i < Size(); ++i)
      for (std::size_t j = 0; j < Size(); ++j) {
        int alive_num = CountAliveAround(i, j);
        /* std::cout << "\n[" << i << "," << j << "] -- " << alive_num << "alive\n"; */

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

  int Cave::CountAliveAround(int i, int j) const {
    int num = 0;

    /* check left */
    if (j != 0 && this->At(i, j - 1) == false) {
      /* std::cout << "left "; */
      ++num;
    }

    /* check left up */
    if (j != 0 && i != 0 && this->At(i - 1, j - 1) == false) {
      ++num;
      /* std::cout << "left up "; */
    }

    /* check up */
    if (i != 0 && this->At(i - 1, j) == false) {
      ++num;
      /* std::cout << "up "; */
    }

    /* check right up */
    if (j != static_cast<int>(Size()) - 1 && i != 0 && this->At(i - 1, j + 1) == false) {
      /* std::cout << "right up "; */
      ++num;
    }

    /* check right */
    if (j != static_cast<int>(Size()) - 1 && this->At(i, j + 1) == false) {
      ++num;
      /* std::cout << "right "; */
    }

    /* check right bottom */
    if (j != static_cast<int>(Size()) - 1 && i != static_cast<int>(Size()) - 1 &&
        this->At(i + 1, j + 1) == false) {
      ++num;
      /* std::cout << "right bot "; */
    }

    /* check bottom */
    if (i != static_cast<int>(Size()) - 1 && this->At(i + 1, j) == false) {
      ++num;
      /* std::cout << "bot "; */
    }

    /* check left bottom */
    if (i != static_cast<int>(Size()) - 1 && j != 0 && this->At(i + 1, j - 1) == false) {
      /* std::cout << "left bot "; */
      ++num;
    }

    return num;
  }

} // namespace cave
