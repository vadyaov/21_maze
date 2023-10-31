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

    for (int num : arr) {
      if (num != 0) {
          uniqueNumbers.insert(num);
      }
    }

    int replacement = 1;
    for (int& num : arr) {
      if (num == 0) {
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
  if (j == 0 && set[j + 1] != set[j]) {
    std::cout << "alone left!\n";
    return true;
  }
  // lonely on the right side
  if (static_cast<std::size_t>(j) == set.size() - 1 && set[j - 1] != set[j]) {
    std::cout << "alone right!\n";
    return true;
  }

  // lonely middle
  return set[j - 1] != set[j] && set[j + 1] != set[j];
}

bool AloneWithoutWall(const std::vector<int>& set, std::vector<Ceil>& cells, int i, int j) {
  int pos = j;
  while (static_cast<std::size_t>(pos) < set.size() - 1 && set[pos] == set[pos + 1]) {
    if (cells[i * set.size() + ++pos].bottm == false) return false;
  }

  pos = j;

  while (static_cast<std::size_t>(pos) != 0 && set[pos - 1] == set[pos]) {
    if (cells[i * set.size() + --pos].bottm == false) return false;
  }

  return true;
}

bool CheckBottomWallRule(const std::vector<int>& set, std::vector<Ceil>& cells, int i, int j) {
  if (Lonely(set, j)) {
    std::cout << "cell " << i << ":" << j << " alone in its set\n";
    return false;
  }
  
  // точно есть соседи, но есть ли у них нижние стенки?
  if (AloneWithoutWall(set, cells, i, j)) {
    std::cout << "cell " << i << ":" << j << " not alone but only has no bot wall\n";
    return false;
  }

  return true;
}

std::vector<Ceil> Eller::GeneratePerfectMaze(int size) {
  std::vector<Ceil> perfect_maze(size * size, {0, 0});

  // 1. first row creation
  std::vector<int> prev(size, 0);
  for (int i = 0; i < size; ++i) {
    std::vector<int> current = prev;

    // remove cells with bottm wall from set
    for (int j = 0; i != 0 && j < size; ++j) {
      if (perfect_maze[(i - 1) * size + j].bottm == true)
        current[j] = 0;
    }

    // 2. join to unique set
    ToUniqueSet(current);

    std::cout << i << ":";
    for (auto k : current)
      std::cout << k << ' ';
    std::cout << "\n";

    // 3. right walls creation
    for (int j = 0; j < size - 1; ++j) {
      if (RandBool() || current[j] == current[j + 1]) {
        perfect_maze[i * size + j].right = true;
      } else {
        /* current[j + 1] = current[j]; */
        int mutable_value = current[j + 1];
        for (int k = 0; k < size; ++k) {
          if (current[k] == mutable_value)
            current[k] = current[j];
        }
      }
    }

    std::cout << i << ":";
    for (auto k : current)
      std::cout << k << ' ';
    std::cout << "\n\n";


    // 4. bottom walls creation
    for (int j = 0; j < size; ++j) {
      if (CheckBottomWallRule(current, perfect_maze, i, j) && RandBool()) {
        /* std::cout << "place bot  wall" << i << ' ' << j << " " << current[j] << std::endl; */
        perfect_maze[i * size + j].bottm = true;
      }
    }


    prev = current;

    /* if (i == 3) break; */

    /* std::cout << "\n\n\n"; */
  }

  // create right and bot corners
  for (int i = 0; i < size; ++i) {
    perfect_maze[i * size + size - 1].right = true;
    perfect_maze[(size - 1) * size + i].bottm = true;
  }


  // NEED TO FIX THIS (MB NEED TO DO part 3 for right walls) WITH CORRECT UNION
  for (int j = 0; j < size - 1; ++j) {
    if (prev[j + 1] != prev[j]) {
      perfect_maze[(size - 1) * size + j].right = false;
      prev[j + 1] = prev[j]; // lishnee
    }
  }

  return perfect_maze;
}

} // namespace maze
