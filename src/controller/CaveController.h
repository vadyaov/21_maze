#ifndef CAVE_CONTROLLER_H_
#define CAVE_CONTROLLER_H_

#include "../model/cave/Cave.h"

namespace cave {

/**
 * @class Controller
 * @brief A class for controlling cave operations.
 *
 * The `Controller` class provides methods for reading, managing, and saving
 * caves.
 */
class Controller {
 public:
  /**
   * @brief Reads a cave from the specified file.
   *
   * @param path The path to the file containing the cave.
   */
  void ReadCave(const std::string& path);

  /**
   * @brief Returns the size of the cave.
   * @return The size of the cave.
   */
  std::size_t Size() const noexcept;

  /**
   * @brief Retrieves the value of the cave cell at the specified coordinates.
   *
   * @param i The horizontal coordinate of the cell.
   * @param j The vertical coordinate of the cell.
   * @return The value at the cell (true or false).
   */
  bool At(int i, int j) const;

  /**
   * @brief Advances the cellular automaton to the next generation.
   *
   * @param life The threshold for cell survival (0-8).
   * @param death The threshold for cell death (0-8).
   */
  void MakeNextGen(int life, int death);

  /**
   * @brief Initializes the cave with the given size and probability.
   *
   * @param size The size of the cave (number of cells).
   * @param prob The probability of cell initialization (0.0 to 1.0).
   */
  void InitializeCave(int size, double prob);

  /**
   * @brief Saves the current cave to a file.
   */
  void Save() const;

 private:
  Cave c; /**< The underlying cave instance. */
};

}  // namespace cave

#endif  // CAVE_CONTROLLER_H_
