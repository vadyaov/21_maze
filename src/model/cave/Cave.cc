#include "Cave.h"

#include <iostream>
#include <random>

namespace cave {

  void Cave::LoadCave(const std::string& path) {
    loader->OpenFile(path);
    ceils_ = loader->ReadCave();
  }

  void Cave::Init(int size, double probability) {
    ceils_.resize(size * size);

    std::random_device rd;
    std::mt19937 engine(rd());
    std::uniform_real_distribution<double> normal_distrib(0.0, 1.0);

    for (int i = 0; i < size * size; ++i) {
      double random_value = normal_distrib(engine);
      std::cout << "Generated " << random_value << std::endl;
      if (random_value <= probability)
        ceils_[i] = false;
      else
        ceils_[i] = true;
    }

  }

  void Cave::NextGeneration(int life_lim, int death_lim) {
    /* std::cout << "life = " << life_lim << " death = " << death_lim << std::endl; */
    std::vector<bool> next = ceils_;

    /* std::cout << "BEFORE:\n"; */
    /* print_cave(); */

    for (std::size_t i = 0; i < Size(); ++i) {
      for (std::size_t j = 0; j < Size(); ++j) {
        int alive_num = CountAliveAround(i, j);
        std::cout << alive_num << " alive ceils around [" << i << ", " << j << "]" << std::endl;
        if (At(i, j) == false && alive_num <= death_lim) { // тут не должно быть меньше либо равно
          next.at(i * Size() + j) = true;
        } else if (At(i, j) == true && alive_num > life_lim) {
          next.at(i * Size() + j) = false;
        }
      }
    }

    ceils_ = next;

    /* std::cout << "AFTER:\n"; */
    /* print_cave(); */
  }

  int Cave::CountAliveAround(int i, int j) const {
    int num = 0;

    /* check left */
    if (j != 0 && this->At(i, j - 1) == false) ++num;

    /* check left up */
    if (j != 0 && i != 0 && this->At(i - 1, j - 1) == false) ++num;

    /* check up */
    if (i != 0 && this->At(i - 1, j) == false) ++num;

    /* check right up */
    if (j != static_cast<int>(Size()) - 1 && i != 0 && this->At(i - 1, j + 1) == false) ++num;

    /* check right */
    if (j != static_cast<int>(Size()) - 1 && this->At(i, j + 1) == false) ++num;

    /* check right bottom */
    if (j != static_cast<int>(Size()) - 1 && i != static_cast<int>(Size()) - 1 &&
        this->At(i + 1, j + 1) == false)
      ++num;

    /* check bottom */
    if (i != static_cast<int>(Size()) - 1 && this->At(i + 1, j) == false) ++num;

    /* check left bottom */
    if (i != static_cast<int>(Size()) - 1 && j != 0 && this->At(i + 1, j - 1) == false)
      ++num;

    return num;
  }

} // namespace cave