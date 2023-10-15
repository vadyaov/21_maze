#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include "../model/maze/Maze.h"

namespace maze {
  class Controller {
    public:
      void ReadMaze(const std::string&);
      void GenMaze(std::size_t);
      void Save() const;
      std::vector<Maze::Coord> FindSolution(Maze::Coord, Maze::Coord);

      std::size_t Size() const noexcept;
      const std::vector<Ceil>& GetCeils() const & noexcept;

      Ceil& At(int, int);

    private:
      Maze m;
  };
} // namespace maze

#endif // CONTROLLER_H_
