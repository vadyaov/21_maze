#ifndef MAZE_H_
#define MAZE_H_

#include <cmath>
#include <utility>

#include "MazeLoader.h"


/**
 * @namespace maze
 * @brief A namespace containing classes for maze-related operations.
 */
namespace maze {

  /**
   * @class Maze
   * @brief A class for handling maze operations.
   *
   * The `Maze` class provides functionality for working with mazes,
   * including loading, generating, finding solutions, and saving to a file.
   */
  class Maze {
    public:
      using Coord = std::pair<int, int>;

      /**
       * @brief Loads a maze from a file.
       *
       * This method loads a maze from the specified file and populates the `ceils_`
       * data member with the maze structure.
       *
       * @param path The path to the file containing the maze.
       * @throw std::invalid_argument If the file path is incorrect or the maze size is invalid.
       */
      void LoadMaze(const std::string& path);

      /**
       * @brief Generates a random maze.
       *
       * Generates a random maze of the specified size using Eller's algorithm
       * and populates the `ceils_` data member with the maze structure.
       *
       * @param size The size of the maze (number of rows and columns).
       */
      void Generate(int size);

      /**
       * @brief Saves the maze to a unique file.
       *
       * Saves the maze to a file with a unique name, including the maze size and a timestamp.
       */
      void SaveToFile() const;

      /**
       * @brief Finds a solution to the maze.
       *
       * Finds a solution to the maze from the specified starting and ending coordinates.
       *
       * @param frst The starting coordinates.
       * @param scnd The ending coordinates.
       * @return A vector of coordinates representing the solution path.
       * @throw std::logic_error If the beginning and ending coordinates are the same.
       */
      std::vector<Coord> FindSolution(const Coord& frst, const Coord& scnd);

      /**
       * @brief Gets the size of the maze.
       *
       * Returns the size of the maze, which is the number of rows or columns.
       *
       * @return The size of the maze.
       */
      std::size_t Size() const noexcept;

      /**
       * @brief Gets a reference to a maze ceil by row and column.
       *
       * Returns a reference to a maze ceil at the specified row and column coordinates.
       *
       * @param row The row coordinate.
       * @param col The column coordinate.
       * @return A reference to the maze ceil.
       * @throw std::out_of_range If the row or column coordinates are out of bounds.
       */
      Ceil& GetCeil(int row, int col);

      /**
       * @brief Gets a const reference to the vector of maze ceils.
       *
       * Returns a const reference to the vector of maze ceils,
       * which represents the maze structure.
       *
       * @return A const reference to the vector of maze ceils.
       */
      const std::vector<Ceil>& GetCeils() const & noexcept;

    private:
      /**
       * @brief Helper method to perform a wave search in the maze.
       *
       * This method is used internally to perform a wave search in the maze structure for finding a solution.
       *
       * @param row The current row coordinate.
       * @param column The current column coordinate.
       * @param steps The current number of steps.
       */
      void MakeWave(int row, int column, int steps);

      /**
       * @brief Helper method to clear step and visit flags in maze ceils.
       *
       * Clears the step and visit flags in all maze ceils, preparing the maze
       * for a new solution search.
       */
      void ClearStepsVisits();

      /**
       * @brief Helper method to find the shortest way in the maze.
       *
       * Finds the shortest way in the maze based on a previously performed wave search.
       *
       * @param finish The finishing coordinates.
       * @return A vector of coordinates representing the shortest path.
       * @throw std::runtime_error If no solution exists.
       */
      std::vector<Coord> FindShortestWay(const Coord& finish);

      /**
       * @brief Helper method to find the next maze ceil in the shortest path.
       *
       * Finds the next maze ceil in the shortest path based on the current coordinates and step information.
       *
       * @param current The current coordinates.
       * @return The coordinates of the next maze ceil in the shortest path.
       * @throw std::logic_error If the maze is impassable.
       */
      Coord FindNextCeil(const Coord& current);

    private:
      std::vector<Ceil> ceils_; /**< The vector of maze ceils representing the maze structure. */

  };
} // namespace maze

#endif // MAZE_H_
