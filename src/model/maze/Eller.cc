#include "Eller.h"

#include <random>
#include <iostream>
#include <unordered_set>

namespace maze {


bool RandBool() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<double> dis(0, 1);

  return dis(gen) < 0.5;
}


/* The Algorithm

    Note: Assume that there all left-most cells have a left-wall and all right-most
          cells have a right wall.

    1. Create the first row. No cells will be members of any set

    2. Join any cells not members of a set to their own unique set

    3. Create right-walls, moving from left to right:
      A. Randomly decide to add a wall or not
        - If the current cell and the cell to the right are members of the same set,
          always create a wall between them. (This prevents loops)
        - If you decide not to add a wall, union the sets to which the current cell
          and the cell to the right are members.

    4. Create bottom-walls, moving from left to right:
      A. Randomly decide to add a wall or not. Make sure that each set has at least
         one cell without a bottom-wall (This prevents isolations)
        - If a cell is the only member of its set, do not create a bottom-wall
        - If a cell is the only member of its set without a bottom-wall, do not create a bottom-wall

    5. Decide to keep adding rows, or stop and complete the maze
      A. If you decide to add another row:
        a. Output the current row
        b. Remove all right walls
        c. Remove cells with a bottom-wall from their set
        d. Remove all bottom walls
        e. Continue from Step 2

      B. If you decide to complete the maze
        a. Add a bottom wall to every cell
        b. Moving from left to right:
          - If the current cell and the cell to the right are members of a different set:
              i.   Remove the right wall
              ii.  Union the sets to which the current cell and cell to the right are members.
              iii. Output the final row

*/

void ToUniqueSet(std::vector<int>& arr) {
    std::unordered_set<int> uniqueNumbers;

    // Перебираем вектор, чтобы найти уникальные числа
    for (int num : arr) {
        if (num != 0) {
            uniqueNumbers.insert(num);
        }
    }

    int replacement = 1;
    for (int& num : arr) {
        if (num == 0) {
            // Заменяем ноль уникальным числом, которого нет во входном массиве
            while (uniqueNumbers.find(replacement) != uniqueNumbers.end()) {
                replacement++;
            }
            num = replacement;
            uniqueNumbers.insert(replacement);
        }
    }

}

bool Lonely(const std::vector<int>& set, int j) {
  // lonely on the left side
  if (j == 0 && set[j + 1] != set[j]) return true;
  // lonely on the right side
  if (static_cast<std::size_t>(j) == set.size() - 1 && set[j - 1] != set[j]) return true;

  // lonely middle
  return set[j - 1] != set[j] && set[j + 1] != set[j];
}

bool AloneWithoutWall(const std::vector<int>& set, std::vector<Ceil>& cells, int i, int j) {
  while (static_cast<std::size_t>(j) < set.size() - 1 && set[j] == set[j + 1]) {
    if (cells[i * set.size() + ++j].bottm == false) return false;
  }

  while (static_cast<std::size_t>(j) != 0 && set[j - 1] == set[j]) {
    if (cells[i * set.size() + --j].bottm == false) return false;
  }

  return true;
}

bool CheckBottomWallRule(const std::vector<int>& set, std::vector<Ceil>& cells, int i, int j) {
  if (Lonely(set, j)) return false;
  
  // точно есть соседи, но есть ли у них нижние стенки?
  if (AloneWithoutWall(set, cells, i, j)) return false;

  return true;
}

std::vector<Ceil> Eller::GeneratePerfectMaze(int size) {
  std::vector<Ceil> perfect_maze(size * size, {0, 0});

    std::vector<int> first(size, 0);
    // 2. join to unique set
    for (int i = 0; i < size; ++i)
      first[i] = i + 1;

    // 3. right walls creation
    for (int j = 0; j < size - 1; ++j) {
      if (RandBool() || first[j] == first[j + 1]) {
        perfect_maze[0 * size + j].right = true;
      } else {
        first[j + 1] = first[j];
      }
    }
    perfect_maze[size - 1].right = true;
    // 4. bottom walls creation
    for (int j = 0; j < size; ++j) {
      if (CheckBottomWallRule(first, perfect_maze, 0, j) && RandBool()) {
        perfect_maze[0 * size + j].bottm = true;
      }
    }

    /* std::cout << "first set:\n"; */
    /* for (auto i : first) */
    /*   std::cout << i << ' '; */
    /* std::cout << "\n\n"; */


  /* std::vector<int> prev(size, 0); */
  for (int i = 1; i < size; ++i) {
    // 1. first row creation
    /* if (i == 4) break; */
    std::vector<int> current = first;

    // remove cells with bottm wall from set
    for (int j = 0; j < size; ++j) {
      if (perfect_maze[(i - 1) * size + j].bottm == true)
        current[j] = 0;
    }

    // 2. join to unique set
    ToUniqueSet(current);

    // 3. right walls creation
    for (int j = 0; j < size; ++j) {
      if (j == size - 1)
        perfect_maze[i * size + j].right = true;
      else if (RandBool() || current[j] == current[j + 1]) {
        perfect_maze[i * size + j].right = true;
      } else {
        current[j + 1] = current[j];
      }
    }

    /* std::cout << "current set:\n"; */
    /* for (auto k : current) */
    /*   std::cout << k << ' '; */
    /* std::cout << "\n\n"; */

    // 4. bottom walls creation
    for (int j = 0; j < size; ++j) {
      if (CheckBottomWallRule(current, perfect_maze, i, j) && RandBool()) {
        /* std::cout << "place bot  wall" << i << ' ' << j << " " << current[j] << std::endl; */
        perfect_maze[i * size + j].bottm = true;
      }
      if (i == size - 1)
        perfect_maze[i * size + j].bottm = true;
    }

    first = current;


    /* std::cout << "\n\n\n"; */
  }

  return perfect_maze;
}

} // namespace maze
