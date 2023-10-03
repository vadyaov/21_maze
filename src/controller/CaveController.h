#ifndef CAVE_CONTROLLER_H_
#define CAVE_CONTROLLER_H_

#include "../model/cave/Cave.h"

namespace cave {

  class Controller {
    public:
      void ReadCave(const std::string& path);
      /* void GenCave(std::size_t size); */

      std::size_t Size() const noexcept;
      /* const std::vector<bool>& GetCeils() const & noexcept; */

      bool At(int i, int j) const;
      /* const bool& At(int i, int j) const; */

      void MakeNextGen(int life, int death);
      void InitializeCave(int size, double prob);

    private:
      Cave c;
  };

} // namespace cave

#endif // CAVE_CONTROLLER_H_
