#ifndef CAVE_H_
#define CAVE_H_

#include <vector>
#include <string>

namespace cave {

  class Cave {
    public:
      Cave() {};
      void LoadCave(const std::string& path);
    private:
      std::vector<bool> ceils_;
  };

} // namespace cave

#endif // CAVE_H_
