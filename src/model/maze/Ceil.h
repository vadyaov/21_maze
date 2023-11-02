#ifndef CEIL_H_
#define CEIL_H_

namespace maze {

/**
 * @struct Ceil
 * @brief Structure representing a cell in a maze.
 *
 * The `Ceil` structure represents a cell in a maze or labyrinth.
 * It contains information about the cell's walls (right and bottom),
 * the number of steps taken to reach the cell, and a flag indicating
 * whether the cell has been visited.
 */
struct Ceil {
  bool right = true; /**< Indicates if there is a right wall for this cell. */
  bool bottm = true; /**< Indicates if there is a bottom wall for this cell. */

  int step = 0;         /**< The number of steps taken to reach this cell. */
  bool visited = false; /**< Flag to indicate whether this cell visited. */
};

}  // namespace maze

#endif  // CEIL_H_
