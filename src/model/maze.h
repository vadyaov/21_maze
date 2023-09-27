#ifndef MAZE_H_
#define MAZE_H_

#include <iostream>

#include <cmath>
#include <vector>
#include <string>

#include <utility>

namespace maze {

  class Ceil {
    public:
      Ceil() : r_wall{true}, d_wall{true}, step{0} {}

      bool IsRight() const noexcept { return r_wall; }
      bool IsDown() const noexcept { return d_wall; }

      bool& GetRight() noexcept { return r_wall; }
      bool& GetDown() noexcept { return d_wall; }

      int& Step() { return step; }
      const int& Step() const { return step; }

    private:
      bool r_wall;
      bool d_wall;

      int step;
  };

  class Maze {
    public:

      using pos = std::pair<int, int>;

      void LoadMaze(const std::string& path);
      void Generate(int size);
      std::vector<pos> FindSolution(const pos& start, const pos& finish);

      /* Getters */
      std::size_t Size() const noexcept;

      Ceil& GetCeil(int row, int col);
      const Ceil& GetCeil(int row, int col) const;

      const std::vector<Ceil>& GetCeils() const & noexcept;

      /* Accessor */
      Ceil& operator()(int, int);

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
          std::cout << ceils_[i].Step() << ' ';
          if (j == std::sqrt(ceils_.size())) {
            std::cout << std::endl;
            j = 0;
          }
        }
      }

    private:
      std::vector<Ceil> ceils_;

      void MakeWave(int row, int column, std::size_t steps);
      void ClearSteps() {
        for (Ceil& c : ceils_)
          c.Step() = 0;
      }
      std::vector<pos> FindShortestWay(const pos&);
      pos FindNextCeil(const pos& begin);
  };
} // namespace maze

#endif // MAZE_H_
