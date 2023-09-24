#include "maze.h"
#include "loader.h"

#include <cstdlib>
#include <ctime>

namespace maze {

  void Maze::LoadMaze(const std::string& path) {
    MazeLoader loader(path);
    loader.ReadWalls(ceils_);
  }

  void Maze::Generate(int size) {
    ceils_.resize(size * size);
    std::vector<int> set(size * size);

    for (int i = 0; i < size * size; ++i)
      set[i] = i;

    // прошелся по лабиринту, поменял рандомно стенки справа. со стекнами снизу
    // пока ниче не делал
    for (int i = 0; i < size; ++i) {
      for (int j = 0; j < size; ++j) {
        int current_ceil = i * size + j;
        bool choice = j == size - 1 ? true : rand() % 2;
        ceils_[current_ceil].GetRight() = choice;

        if (choice == false && set[current_ceil] != set[current_ceil + 1]) {
          int set_a = set[current_ceil];
          int set_b = set[current_ceil + 1];

          for (int i = 0; i < size * size; ++i)
            if (set[i] == set_b) set[i] = set_a;
        }

      }
    }

    std::srand(std::time(nullptr));

  }

  std::size_t Maze::Size() const noexcept {
    return ceils_.size();
  }

  const std::vector<Ceil>& Maze::GetCeils() const & noexcept {
    return ceils_;
  }

  Ceil& Maze::operator()(int i, int j) {
    if (i < 0 || j < 0)
      throw std::invalid_argument("Incorrect i or j for operator()");
    return ceils_[i * std::sqrt(Size()) + j];
  }

}
