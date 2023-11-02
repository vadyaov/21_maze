#ifndef CAVE_H_
#define CAVE_H_

#include "CaveLoader.h"

namespace cave {

/**
 * @class Cave
 *
 * @brief Represents a cave for cellular automata simulations.
 */
class Cave {
 public:
  /**
   * @brief Loads the cave from a file.
   *
   * @param path The path to the file containing cave data.
   */
  void LoadCave(const std::string& path);

  /**
   * @brief Returns the size of the cave.
   *
   * @return The size of the cave as sqrt of the number of cells.
   */
  std::size_t Size() const noexcept;

  /**
   * @brief Retrieves the value at the specified cell position.
   *
   * @param row The row (horizontal) coordinate of the cell.
   * @param col The column (vertical) coordinate of the cell.
   *
   * @return The value at the cell (true or false).
   */
  bool At(int row, int col) const;

  /**
   * @brief Initializes the cave with a given size and fills it with random
   * values.
   *
   * @param size The size of the cave (number of rows and columns).
   * @param probability The probability of filling a cell with a live state (0.0
   * to 1.0).
   */
  void Init(int size, double probability);

  /**
   * @brief Advances the cellular automaton to the next generation.
   *
   * @param life_lim The threshold for cell survival (1-7), determining whether
   * a cell survives.
   * @param death_lim The threshold for cell death (1-7), determining whether a
   * cell dies.
   */
  void NextGeneration(int life_lim, int death_lim);

 private:
  /**
   * @brief Counts the number of live neighbors around a specified cell.
   * @param i The row (horizontal) coordinate of the cell.
   * @param j The column (vertical) coordinate of the cell.
   * @return The number of live neighbors around the cell.
   */
  int CountAliveAround(std::size_t i, std::size_t j) const;

 private:
  std::vector<bool>
      ceils_; /**< An array representing the state of cells in the cave. */
};

}  // namespace cave

#endif  // CAVE_H_
