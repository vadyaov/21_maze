#ifndef ELLER_H_
#define ELLER_H_

#include <vector>
#include "Ceil.h"

namespace maze {

  class Eller {
    public:
      static std::vector<Ceil> GeneratePerfectMaze(int size);
  };

} // namespace maze

#endif // ELLER_H_
