#ifndef CAVE_H_
#define CAVE_H_

#include "CaveLoader.h"

#include <iostream>
#include <cmath>

namespace cave {

  class Cave {
    public:
      Cave() : loader{new CaveLoader} {}
      ~Cave() { delete loader; }

      void LoadCave(const std::string& path);
      /* void Generate(int size); */

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

    private:
      CaveLoader* loader;
      std::vector<bool> ceils_;
  };

} // namespace cave

#endif // CAVE_H_
