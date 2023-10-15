#ifndef CAVE_H_
#define CAVE_H_

#include "CaveLoader.h"

#include <iostream>
#include <cmath>

namespace cave {

  class Cave {
    public:
      void LoadCave(const std::string&);

      std::size_t Size() const noexcept;

      int At(int, int) const;

      void Init(int, double);
      void NextGeneration(int, int);

    private:
      int CountAliveAround(int, int) const;

    private:
      std::vector<bool> ceils_;
  };

} // namespace cave

#endif // CAVE_H_
