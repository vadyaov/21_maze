#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include "../model/maze/Maze.h"

namespace maze {

/**
 * @class Controller
 * @brief A class for controlling maze operations.
 *
 * The `Controller` class provides methods for reading, generating, and
 * manipulating mazes.
 */
class Controller {
 public:
  /**
   * @brief Reads a maze from the specified file.
   *
   * @param path The path to the file containing the maze.
   */
  void ReadMaze(const std::string& path);

  /**
   * @brief Generates a new maze of the given size.
   *
   * @param size The size of the maze to be generated.
   */
  void GenMaze(std::size_t size);

  /**
   * @brief Finds a solution path in the maze between two coordinates.
   *
   * @param first The starting coordinate.
   * @param second The destination coordinate.
   * @return A vector of coordinates representing the solution path.
   */
  std::vector<Maze::Coord> FindSolution(Maze::Coord first, Maze::Coord second);

  /**
   * @brief Returns the size of the maze.
   * @return The size of the maze.
   */
  std::size_t Size() const noexcept;

  /**
   * @brief Returns a constant reference to the maze cells.
   * @return A constant reference to the vector of maze cells.
   */
  const std::vector<Ceil>& GetCeils() const& noexcept;

  /**
   * @brief Accesses a maze cell by its coordinates.
   * @param i The row (horizontal) coordinate of the cell.
   * @param j The column (vertical) coordinate of the cell.
   * @return A reference to the maze cell.
   */
  Ceil& At(int i, int j);

  /**
   * @brief Saves the current maze to a file.
   */
  void Save() const;

  /**
   * @brief Clears the current maze.
   */
  void Clear() noexcept;

 private:
  Maze m; /**< The underlying maze instance. */
};
}  // namespace maze

#endif  // CONTROLLER_H_
