#include "Cave.h"

#include <iostream>

namespace cave {

  void Cave::LoadCave(const std::string& path) {
    loader->OpenFile(path);
    ceils_ = loader->ReadCave();
    print_cave();
  }

  void Cave::NextGeneration(int life_lim, int death_lim) {
    std::cout << "life = " << life_lim << " death = " << death_lim << std::endl;
    std::vector<bool> next(ceils_.size());

    for (std::size_t i = 0; i < Size(); ++i) {
      for (std::size_t j = 0; j < Size(); ++j) {
        int alive_num = CountAliveAround(i, j);
        std::cout << i << ':' << j << " " << alive_num << " alive ";
        if (this->At(i, j) == false && alive_num < death_lim) {
          next.at(i * Size() + j) = true;
        } else if (this->At(i, j) == true && alive_num > life_lim) {
          next.at(i * Size() + j) = false;
        } else {
          next.at(i * Size() + j) = this->At(i, j);
        }
      }
    }

    ceils_ = next;

    print_cave();
  }

  int Cave::CountAliveAround(int i, int j) {
    int num = 0;

    /* check left */
    if (j != 0 && this->At(i, j - 1) == false) {
      ++num;
      /* std::cout << "left\n"; */
    }

    /* check left up */
    if (j != 0 && i != 0 && this->At(i - 1, j - 1) == false) {
      ++num;
      /* std::cout << "left up\n"; */
    }

    /* check up */
    if (i != 0 && this->At(i - 1, j) == false) {
      ++num;
      /* std::cout << "up\n"; */
    }

    /* check right up */
    if (j != static_cast<int>(Size()) - 1 && i != 0 && this->At(i - 1, j + 1) == false) {
      ++num;
      /* std::cout << "right up\n"; */
    }

    /* check right */
    if (j != static_cast<int>(Size()) - 1 && this->At(i, j + 1) == false) {
      ++num;
      /* std::cout << "right\n"; */
    }

    /* check right bottom */
    if (j != static_cast<int>(Size()) - 1 && i != static_cast<int>(Size()) - 1 &&
        this->At(i + 1, j + 1) == false) {
      ++num;
      /* std::cout << "right btm\n"; */
    }

    /* check bottom */
    if (i != static_cast<int>(Size()) - 1 && this->At(i + 1, j) == false) {
      ++num;
      /* std::cout << "btm\n"; */
    }

    /* check left bottom */
    if (i != static_cast<int>(Size()) - 1 && j != 0 && this->At(i + 1, j - 1) == false) {
      ++num;
      /* std::cout << "left btm\n"; */
    }

    return num;
  }

} // namespace cave
