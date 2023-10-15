#ifndef CAVE_CONTROLLER_H_
#define CAVE_CONTROLLER_H_

#include "../model/cave/Cave.h"

namespace cave {

  class Controller {
    public:
      void ReadCave(const std::string&);

      std::size_t Size() const noexcept;

      bool At(int, int) const;

      void MakeNextGen(int, int);
      void InitializeCave(int, double);
      void Save() const;

    private:
      Cave c;
  };

} // namespace cave

#endif // CAVE_CONTROLLER_H_
