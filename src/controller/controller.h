#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include "../model/maze.h"

namespace maze {
  class Controller {
    public:
      void ReadMaze(const std::string& path);
      void GenMaze(std::size_t size);

      void print() {m.print();}

      std::size_t Size() const noexcept;
      const std::vector<Ceil>& GetCeils() const & noexcept;
      /* const std::vector<std::vector<bool>>& GetVerticalWalls() const & noexcept; */
      /* const std::vector<std::vector<bool>>& GetHorizontalWalls() const & noexcept; */

    private:
      Maze m;
  };
} // namespace maze

#endif // CONTROLLER_H_
