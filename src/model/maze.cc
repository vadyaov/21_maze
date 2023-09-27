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

  std::vector<Maze::pos> Maze::FindSolution(const pos& frst, const pos& scnd) {
    if (frst == scnd)
      throw std::logic_error("'Begin' and 'End' ceils are the same");

    ClearSteps();

    std::cout << "First point\nx " << frst.first << ", y " << frst.second << std::endl;
    std::cout << "Second point\nx " << scnd.first << ", y " << scnd.second << std::endl;

    MakeWave(frst.first, frst.second, 0);
    GetCeil(frst.first, frst.second).Step() = 0;

    print_steps();

    return FindShortestWay(scnd);
  }

  void Maze::MakeWave(int row, int column, std::size_t steps) {
    Ceil& current_ceil = GetCeil(row, column);
    int &step = current_ceil.Step();

    if (step != 0) return;
    step = steps;

    if (!current_ceil.IsRight())
      MakeWave(row, column + 1, steps + 1);
    if (!current_ceil.IsDown())
      MakeWave(row + 1, column, steps + 1);
    if (column > 0 && !GetCeil(row, column - 1).IsRight())
      MakeWave(row, column - 1, steps + 1);
    if (row > 0 && !GetCeil(row - 1, column).IsDown())
      MakeWave(row - 1, column, steps + 1);
  }

  std::vector<Maze::pos> Maze::FindShortestWay(const pos& biggest_wave) {
    std::vector<Maze::pos> shortest;
    for (pos next = biggest_wave; GetCeil(next.first, next.second).Step() != 0; next = FindNextCeil(next)) {
      shortest.push_back(next);
    }

    for (auto p : shortest) {
      std::cout << p.first << "  " << p.second << std::endl;
    }

    return shortest;
  }

  // Bad function cause i'm tired and cant't think good
  // Got Something very bad and infinite recursion))
  Maze::pos Maze::FindNextCeil(const pos& current) {
    const std::size_t i = current.first, j = current.second;
    const int current_step = GetCeil(i, j).Step();
    std::cout << "Current step = " << current_step << std::endl;
    pos p;

    if (j > 0 && GetCeil(i, j - 1).Step() == current_step - 1 && !GetCeil(i, j - 1).IsRight())
      p = {i, j - 1};
    else if (i > 0 && GetCeil(i - 1, j).Step() == current_step - 1 && !GetCeil(i - 1, j).IsDown())
      p = {i - 1, j};
    else if (j < Size() - 1 && GetCeil(i, j + 1).Step() == current_step - 1 && !GetCeil(i, j + 1).IsRight())
      p = {i, j + 1};
    else if (i < Size() - 1 && GetCeil(i + 1, j).Step() == current_step - 1 && !GetCeil(i + 1, j).IsDown())
      p = {i + 1, j};
    else {
      std::cout << "Something very BAD\n";
    }

    return p;
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

  Ceil& Maze::operator()(int i, int j) {
    if (i < 0 || j < 0 || (size_t)i > Size() || (size_t)j > Size())
      throw std::invalid_argument("Incorrect i or j for operator()");
    return ceils_[i * Size() + j];
  }

}
