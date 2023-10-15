#ifndef MAZE_H_
#define MAZE_H_

#include <cmath>
#include <utility>

#include "MazeLoader.h"

namespace maze {

  class Maze {
    public:
      using Coord = std::pair<int, int>;

      void LoadMaze(const std::string&);
      void Generate(int);
      void SaveToFile() const;
      std::vector<Coord> FindSolution(const Coord&, const Coord&);

      std::size_t Size() const noexcept;
      Ceil& GetCeil(int, int);
      const std::vector<Ceil>& GetCeils() const & noexcept;

    private:
      void MakeWave(int, int, int);
      void ClearStepsVisits();
      std::vector<Coord> FindShortestWay(const Coord&);
      Coord FindNextCeil(const Coord&);

    private:
      std::vector<Ceil> ceils_;

  };
} // namespace maze

#endif // MAZE_H_

      /* /1* debug *1/ */
      /* void print() { */
      /*   std::cout << "Size = " << ceils_.size() << std::endl; */

      /*   for (std::size_t i = 0, j = 1; i < ceils_.size(); ++i, ++j) { */
      /*     std::cout << ceils_[i].right << ' '; */
      /*     if (j == std::sqrt(ceils_.size())) { */
      /*       std::cout << std::endl; */
      /*       j = 0; */
      /*     } */
      /*   } */

      /*   std::cout << std::endl; */

      /*   for (std::size_t i = 0, j = 1; i < ceils_.size(); ++i, ++j) { */
      /*     std::cout << ceils_[i].bottm << ' '; */
      /*     if (j == std::sqrt(ceils_.size())) { */
      /*       std::cout << std::endl; */
      /*       j = 0; */
      /*     } */
      /*   } */

      /*   std::cout << std::endl; */
      /* } */

      /* void print_steps() { */
      /*   for (std::size_t i = 0, j = 1; i < ceils_.size(); ++i, ++j) { */
      /*     std::cout << ceils_[i].step << ' '; */
      /*     if (j == std::sqrt(ceils_.size())) { */
      /*       std::cout << std::endl; */
      /*       j = 0; */
      /*     } */
      /*   } */
      /* } */

