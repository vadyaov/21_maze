#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include "../model/maze.h"

namespace maze {
  class Controller {
    public:
      void ReadMaze(const std::string& path);
      void GenMaze(std::size_t size);
      std::vector<Maze::Coord> FindSolution(Maze::Coord first, Maze::Coord second);

      void print() {m.print();}

      std::size_t Size() const noexcept;
      const std::vector<Ceil>& GetCeils() const & noexcept;

      Ceil& At(int i, int j) { return m(i, j); }

    private:
      Maze m;
  };
} // namespace maze

#endif // CONTROLLER_H_
