#ifndef MAZE_H_
#define MAZE_H_

#include <iostream>
#include <cmath>
#include <utility>

#include "MazeLoader.h"

namespace maze {

  class Maze {
    public:
      Maze() : loader{new MazeLoader} {}
      ~Maze() { delete loader; }

      using Coord = std::pair<int, int>;

      void LoadMaze(const std::string& path);
      void Generate(int size);
      std::vector<Coord> FindSolution(const Coord& start, const Coord& finish);

      /* Getters */
      std::size_t Size() const noexcept;
      Ceil& GetCeil(int row, int col);
      const Ceil& GetCeil(int row, int col) const;
      const std::vector<Ceil>& GetCeils() const & noexcept;

      /* debug */
      void print() {
        std::cout << "Size = " << ceils_.size() << std::endl;

        for (std::size_t i = 0, j = 1; i < ceils_.size(); ++i, ++j) {
          std::cout << ceils_[i].IsRight() << ' ';
          if (j == std::sqrt(ceils_.size())) {
            std::cout << std::endl;
            j = 0;
          }
        }

        std::cout << std::endl;

        for (std::size_t i = 0, j = 1; i < ceils_.size(); ++i, ++j) {
          std::cout << ceils_[i].IsDown() << ' ';
          if (j == std::sqrt(ceils_.size())) {
            std::cout << std::endl;
            j = 0;
          }
        }

        std::cout << std::endl;
      }

      void print_steps() {
        for (std::size_t i = 0, j = 1; i < ceils_.size(); ++i, ++j) {
          std::cout << ceils_[i].step << ' ';
          if (j == std::sqrt(ceils_.size())) {
            std::cout << std::endl;
            j = 0;
          }
        }
      }

    private:
      MazeLoader* loader;
      std::vector<Ceil> ceils_;

      void MakeWave(int row, int column, std::size_t steps);
      void ClearSteps() {
        for (Ceil& c : ceils_) {
          c.step = 0;
          c.visited = false;
        }
      }
      std::vector<Coord> FindShortestWay(const Coord&);
      Coord FindNextCeil(const Coord& begin);
  };
} // namespace maze

#endif // MAZE_H_
