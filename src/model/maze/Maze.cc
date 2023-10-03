#include "Maze.h"

#include <cstdlib>
#include <ctime>

namespace maze {

  void Maze::LoadMaze(const std::string& path) {
    loader->OpenFile(path);
    ceils_ = loader->ReadMaze();
  }

  void Maze::Generate(int size) {
    ceils_.resize(size * size);
    std::vector<int> set(size * size);

    std::srand(std::time(nullptr));

    for (int i = 0; i < size * size; ++i)
      set[i] = i;

    // прошелся по лабиринту, поменял рандомно стенки справа. со стекнами снизу
    // пока ниче не делал
    for (int i = 0; i < size; ++i)
      for (int j = 0; j < size; ++j) {

        int current_ceil = i * size + j;
        bool choice = j == size - 1 ? true : rand() % 2;
        ceils_[current_ceil].GetRight() = choice;

        if (choice == false && set[current_ceil] != set[current_ceil + 1]) {

          int set_a = set[current_ceil];
          int set_b = set[current_ceil + 1];

          for (int k = 0; k < size * size; ++k)
            if (set[k] == set_b) set[k] = set_a;

        }

      }
  }

  std::vector<Maze::Coord> Maze::FindSolution(const Coord& frst, const Coord& scnd) {
    if (frst == scnd)
      throw std::logic_error("'Begin' and 'End' ceils are the same");

    ClearSteps();

    MakeWave(frst.first, frst.second, 0);
    /* print_steps(); */

    return FindShortestWay(scnd);
  }

  void Maze::MakeWave(int row, int column, std::size_t steps) {
    Ceil& current_ceil = GetCeil(row, column);

    if (current_ceil.visited == true) return;

    current_ceil.step = steps;
    current_ceil.visited = true;

    if (!current_ceil.IsRight())
      MakeWave(row, column + 1, steps + 1);

    if (!current_ceil.IsDown())
      MakeWave(row + 1, column, steps + 1);

    if (column > 0 && !GetCeil(row, column - 1).IsRight())
      MakeWave(row, column - 1, steps + 1);

    if (row > 0 && !GetCeil(row - 1, column).IsDown())
      MakeWave(row - 1, column, steps + 1);
  }

  std::vector<Maze::Coord> Maze::FindShortestWay(const Coord& finish) {
    if (GetCeil(finish.first, finish.second).step == 0)
      throw std::runtime_error("Solution doesn't exist.");

    std::vector<Maze::Coord> shortest;
    Coord next{finish};

    while (GetCeil(next.first, next.second).step != 0) {
      next = FindNextCeil(next);
      shortest.push_back(next);
    }

    return shortest;
  }

  Maze::Coord Maze::FindNextCeil(const Coord& current) {
    const std::size_t i = current.first;
    const std::size_t j = current.second;
    const int current_step = GetCeil(i, j).step;

    // ceil is not on the left side so we can check (row, col - 1) ceil
    if (j != 0) {
      if (GetCeil(i, j - 1).step == current_step - 1 && !GetCeil(i, j - 1).IsRight())
        return {i, j - 1};
    }

    // ceil is not on the top so we can check (row - 1, col) ceil
    if (i != 0) {
      if (GetCeil(i - 1, j).step == current_step - 1 && !GetCeil(i - 1, j).IsDown())
        return {i - 1, j};
    }

    // ceil is not on the right side so we can check (row, col + 1)
    if (j != Size() - 1) {
      if (GetCeil(i, j + 1).step == current_step - 1 && !GetCeil(i, j).IsRight())
        return {i, j + 1};
    }

    // ceil is not on the bot so we can check (row + 1, col)
    if (i != Size() - 1) {
      if (GetCeil(i + 1, j).step == current_step - 1 && !GetCeil(i, j).IsDown())
        return {i + 1, j};
    }

    throw std::logic_error("Impassable maze");
  }

  std::size_t Maze::Size() const noexcept {
    return std::sqrt(ceils_.size());
  }

  Ceil& Maze::GetCeil(int row, int col) {
    if ((row < 0 || static_cast<size_t>(row) >= Size()) ||
        (col < 0 || static_cast<size_t>(col) >= Size()))
      throw std::invalid_argument("Incorrect i or j for operator()");
    return ceils_[row * Size() + col];
  }

  const Ceil& Maze::GetCeil(int row, int col) const {
    if ((row < 0 || static_cast<size_t>(row) >= Size()) ||
        (col < 0 || static_cast<size_t>(col) >= Size()))
      throw std::invalid_argument("Incorrect i or j for operator()");
    return ceils_[row * Size() + col];
  }

  const std::vector<Ceil>& Maze::GetCeils() const & noexcept {
    return ceils_;
  }

} // namespace maze