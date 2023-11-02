#ifndef ELLER_H_
#define ELLER_H_

#include <vector>
#include "Ceil.h"

/**
 * @namespace maze
 * @brief A namespace containing classes for maze-related operations.
 */
namespace maze {

  /**
   * @class Eller
   * @brief A class for generating perfect maze.
   *
   * The `Eller` class provides only 1 static method for generate perfect maze.
   */
  class Eller {
    public:
      /**
       * @brief Generating perfect maze of size 'size'.
       *
       * @param size The size of the maze.
       */
      static std::vector<Ceil> GeneratePerfectMaze(int size);
  };

} // namespace maze

#endif // ELLER_H_
