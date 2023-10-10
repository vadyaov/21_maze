#ifndef CAVE_H_
#define CAVE_H_

#include "CaveLoader.h"

#include <iostream>
#include <cmath>

namespace cave {

  class Cave {
    public:
      void LoadCave(const std::string& path);

      std::size_t Size() const noexcept {
        return std::sqrt(ceils_.size());
      }

      int At(int i, int j) const {
        return ceils_.at(i * Size() + j);
      }

      void print_cave() {
        std::cout << "Size = " << ceils_.size() << std::endl;

        for (std::size_t i = 0, j = 1; i < ceils_.size(); ++i, ++j) {
          std::cout << ceils_[i] << ' ';
          if (j == std::sqrt(ceils_.size())) {
            std::cout << std::endl;
            j = 0;
          }
        }
      }

      void Init(int, double);
      void NextGeneration(int, int);

    private:
      int CountAliveAround(int, int) const;

    private:
      std::vector<bool> ceils_;
  };

} // namespace cave

#endif // CAVE_H_
