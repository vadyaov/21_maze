#include "Maze.h"

#include <iostream>
#include <ctime>
#include <algorithm>
#include <random>
#include <numeric>

namespace maze {

  void Maze::LoadMaze(const std::string& path) {
    MazeLoader loader;
    loader.OpenFile(path);
    ceils_ = loader.ReadMaze();
  }

  /*
  1. Инициализируйте ячейки первой строки, так чтобы каждая ячейка принадлежала
    своему собственному множеству.

  2. Затем случайным образом объединяйте соседние ячейки, но только если они не
    принадлежат одному и тому же множеству. При объединении ячеек объедините
    множества обеих ячеек в одно, указывая, что все ячейки в обоих множествах
    теперь соединены (существует путь, соединяющий любые две ячейки в множестве).

  3. Для каждого множества случайным образом создайте вертикальные связи вниз к
    следующей строке. Все оставшиеся множества должны иметь как минимум одну
    вертикальную связь. Ячейки в следующей строке, соединенные таким образом,
    должны принадлежать множеству ячейки выше.

  4. Заполните оставшиеся ячейки в следующей строке, помещая их в собственные множества.
    Повторяйте процесс до достижения последней строки.

  5. Для последней строки объедините все соседние ячейки, не принадлежащие одному
    и тому же множеству, и уберите вертикальные связи. Готово!
  */
  bool RandomChoice() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1);

    return dis(gen) < 0.5 ? true : false;
  }

  void Maze::Generate(int size) {
    ceils_.resize(size * size);
    std::fill(ceils_.begin(), ceils_.end(), Ceil());
    std::vector<int> myset(size * size, 0); // set for all cells


    for (int i = 0; i < size; ++i) {

      {
      // 1. fill the first line set
      int start = i * size + 1;
      for (int j = 0; j < size; ++j)
        if (myset[i * size + j] == 0)
          myset[i * size + j] = start++;
      }

      // 2. Walk through row and place right walls
      for (int j = 0; j < size - 1; ++j) {
        int &curr_set_value = myset[i * size + j];
        int &right_set_value = myset[i * size + j + 1];

        if (curr_set_value != right_set_value && RandomChoice()) {
          right_set_value = curr_set_value;
          GetCeil(i, j).right = false;
        }
      }

      // 3. Walk through row and place bottm walls
      if (i != size - 1) {

        for (int j = 0; j < size; ++j) {
          if (RandomChoice()) {
            myset[(i + 1) * size + j] = myset[i * size + j];
            GetCeil(i, j).bottm = false;
          }
        }

        // 3.1 check for at least one bottm not wall
        bool placed = !GetCeil(i, 0).bottm;
        for (int j = 1; j < size; ++j) {
          int curr_set_value = myset[i * size + j];
          int prev_set_value = myset[i * size + j - 1];

          /* std::cout << "i: " << i << " j: " << j << std::endl; */
          /* std::cout << "curr: " << curr_set_value << " prev: " << prev_set_value << std::endl; */
          /* std::cout << "placed = " << placed << std::endl; */

          if (prev_set_value != curr_set_value) {
            if (placed == false) {
              GetCeil(i, j - 1).bottm = false;
              myset[(i + 1) * size + j - 1] = prev_set_value;
            }
            placed = false;
          }

          if (GetCeil(i, j).bottm == false) placed = true;

          if (j == size - 1 && placed == false) {
              GetCeil(i, j).bottm = false;
              myset[(i + 1) * size + j] = curr_set_value;
          }
        }

      }

    for (std::size_t k = 0, j = 1; k < myset.size(); ++k, ++j) {
      std::cout << myset[k] << ' ';
      if (j == (size_t)size) {
        std::cout << std::endl;
        j = 0;
      }
    }
    std::cout << std::endl;

    }

      // 4 Last row merge different cells
    for (int i = size - 1, j = 0; j < size - 1; ++j) {
      if (myset[i * size + j] != myset[i * size + j + 1]) {
        myset[i * size + j + 1] = myset[i * size + j];
        GetCeil(i, j).right = false;
      }
    }



    std::cout << "AFTER ALGO\n";
    for (std::size_t i = 0, j = 1; i < myset.size(); ++i, ++j) {
      std::cout << myset[i] << ' ';
      if (j == (size_t)size) {
        std::cout << std::endl;
        j = 0;
      }
    }
    std::cout << std::endl;

  }

  std::vector<Maze::Coord> Maze::FindSolution(const Coord& frst, const Coord& scnd) {
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

    if (!current_ceil.right)
      MakeWave(row, column + 1, steps + 1);

    if (!current_ceil.bottm)
      MakeWave(row + 1, column, steps + 1);

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

  std::size_t Maze::Size() const noexcept {
    return std::sqrt(ceils_.size());
  }

  Ceil& Maze::GetCeil(int row, int col) {
    if ((row < 0 || static_cast<size_t>(row) >= Size()) ||
        (col < 0 || static_cast<size_t>(col) >= Size()))
      throw std::out_of_range("Incorrect i or j for operator()");
    return ceils_[row * Size() + col];
  }

  const std::vector<Ceil>& Maze::GetCeils() const & noexcept {
    return ceils_;
  }

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

} // namespace maze
