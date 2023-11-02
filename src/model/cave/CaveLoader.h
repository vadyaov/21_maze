#ifndef CAVE_LOADER_H_
#define CAVE_LOADER_H_

#include "../BaseLoader.h"

/**
 * @namespace cave
 * @brief A namespace containing classes for cave-related operations.
 */
namespace cave {

/**
 * @class CaveLoader
 * @brief A class for loading cave information from a file.
 *
 * The `CaveLoader` class is responsible for reading maze information from
 * a file and populating a vector of cave cells.
 *
 * Inherits from BaseLoader.
 */
class CaveLoader : public BaseLoader {
 public:
  /**
   * @brief Reads cave information from the currently opened file.
   *
   * This method reads the structure of a cave from the file and populates
   * a vector of cave cells with the information. The `sz_` member variable
   * is used to determine the size of the cave.
   *
   * @return A vector of cave cells representing the cave structure.
   */
  std::vector<bool> ReadCave();
};

}  // namespace cave

#endif  // CAVE_LOADER_H_
