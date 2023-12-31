#include "Maze.h"

#include <algorithm>
#include <ctime>

#include "Eller.h"

namespace maze {

void Maze::LoadMaze(const std::string& path) {
  MazeLoader loader;
  loader.OpenFile(path);
  ceils_ = loader.ReadMaze();
}

void Maze::Generate(int size) { ceils_ = Eller::GeneratePerfectMaze(size); }

std::vector<Maze::Coord> Maze::FindSolution(const Coord& frst,
                                            const Coord& scnd) {
  if (frst == scnd)
    throw std::logic_error("'Begin' and 'End' ceils are the same");

  ClearStepsVisits();
  MakeWave(frst.first, frst.second, 0);

  return FindShortestWay(scnd);
}

void Maze::MakeWave(int row, int column, int steps) {
  Ceil& current_ceil = GetCeil(row, column);

  if (current_ceil.visited == true) return;

  current_ceil.step = steps;
  current_ceil.visited = true;

  if (!current_ceil.right) MakeWave(row, column + 1, steps + 1);

  if (!current_ceil.bottm) MakeWave(row + 1, column, steps + 1);

  if (column > 0 && !GetCeil(row, column - 1).right)
    MakeWave(row, column - 1, steps + 1);

  if (row > 0 && !GetCeil(row - 1, column).bottm)
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
    if (GetCeil(i, j - 1).step == current_step - 1 && !GetCeil(i, j - 1).right)
      return {i, j - 1};
  }

  // ceil is not on the top so we can check (row - 1, col) ceil
  if (i != 0) {
    if (GetCeil(i - 1, j).step == current_step - 1 && !GetCeil(i - 1, j).bottm)
      return {i - 1, j};
  }

  // ceil is not on the right side so we can check (row, col + 1)
  if (j != Size() - 1) {
    if (GetCeil(i, j + 1).step == current_step - 1 && !GetCeil(i, j).right)
      return {i, j + 1};
  }

  // ceil is not on the bot so we can check (row + 1, col)
  if (i != Size() - 1) {
    if (GetCeil(i + 1, j).step == current_step - 1 && !GetCeil(i, j).bottm)
      return {i + 1, j};
  }

  throw std::logic_error("Impassable maze");
}

void Maze::ClearStepsVisits() {
  for (Ceil& c : ceils_) {
    c.step = 0;
    c.visited = false;
  }
}

std::size_t Maze::Size() const noexcept { return std::sqrt(ceils_.size()); }

Ceil& Maze::GetCeil(int row, int col) {
  if ((row < 0 || static_cast<size_t>(row) >= Size()) ||
      (col < 0 || static_cast<size_t>(col) >= Size()))
    throw std::out_of_range("Incorrect i or j for operator()");
  return ceils_[row * Size() + col];
}

const std::vector<Ceil>& Maze::GetCeils() const& noexcept { return ceils_; }

std::string GenerateUniqueName(std::size_t size) {
  std::string sz = std::to_string(size);
  std::string basename{"./examples/maze_" + sz + "x" + sz + "_"};

  std::time_t now = std::time(nullptr);
  std::string now_str = std::ctime(&now);

  now_str.pop_back();

  return basename + now_str + ".txt";
}

void Maze::SaveToFile() const {
  if (ceils_.empty()) return;

  std::string filename = GenerateUniqueName(Size());

  std::fstream filestream;
  filestream.open(filename, std::ios_base::out);

  filestream << Size() << ' ' << Size() << std::endl;
  for (std::size_t i = 0, j = 1; i < ceils_.size(); ++i, ++j) {
    filestream << ceils_[i].right << ' ';
    if (j == Size()) {
      filestream << std::endl;
      j = 0;
    }
  }

  filestream << std::endl;

  for (std::size_t i = 0, j = 1; i < ceils_.size(); ++i, ++j) {
    filestream << ceils_[i].bottm << ' ';
    if (j == Size()) {
      filestream << std::endl;
      j = 0;
    }
  }

  filestream.close();
}

void Maze::Clear() noexcept { ceils_.clear(); }

}  // namespace maze
