#ifndef MAZE_LOADER_H_
#define MAZE_LOADER_H_

#include "../BaseLoader.h"
#include "Ceil.h"

/**
 * @namespace maze
 * @brief A namespace containing classes for maze-related operations.
 */
namespace maze {

  /**
   * @class MazeLoader
   * @brief A class for loading maze information from a file.
   *
   * The `MazeLoader` class is responsible for reading maze information from
   * a file and populating a vector of maze cells.
   *
   * Inherits from BaseLoader.
   */
  class MazeLoader : public BaseLoader {
    public:
      /**
       * @brief Reads maze information from the currently opened file.
       *
       * This method reads the structure of a maze from the file and populates
       * a vector of maze cells with the information. The `sz_` member variable
       * is used to determine the size of the maze.
       *
       * @return A vector of maze cells representing the maze structure.
       */
      std::vector<Ceil> ReadMaze();
  };
} // namespace maze

#endif // MAZE_LOADER_H_
