#ifndef BASE_LOADER_H_
#define BASE_LOADER_H_

#include <fstream>
#include <string>
#include <vector>

/**
 * @class BaseLoader
 * @brief A class providing methods for opening and closing a file
 *        for reading and storing the size of a maze/cave.
 *
 * The `BaseLoader` class is designed to handle the loading of maze or cave
 * information from a file. It provides methods to open and close the file,
 * as well as storing the size of the maze or cave.
 */
class BaseLoader {
 public:
  /**
   * @brief Default constructor for the BaseLoader class.
   *
   * Initializes the input file stream and sets the size of the maze/cave to
   * zero.
   */
  BaseLoader() : istrm_{}, sz_{0} {}

  /**
   * @brief Opens a file for reading maze or cave information.
   *
   * This method opens the specified file at the given path for reading.
   * It checks if the file was successfully opened and reads the size of the
   * maze/cave. If the file path is incorrect, it throws an
   * `std::invalid_argument` exception. If the size is incorrect (e.g., not a
   * square maze, size greater than 50, or size less than 2), it also throws an
   * exception.
   *
   * @param path The path to the file to be opened.
   * @throw std::invalid_argument If the file path is incorrect or the maze/cave
   * size is invalid.
   */
  void OpenFile(const std::string& path) {
    istrm_.open(path);
    if (!istrm_.is_open()) throw std::invalid_argument("Incorrect path.");

    int rows, columns;
    istrm_ >> rows >> columns;

    if (rows != columns || rows > 50 || rows < 2)
      throw std::invalid_argument("Incorrect size.");

    sz_ = rows;
  }

  /**
   * @brief Closes the currently opened file.
   *
   * This method closes the file that was previously opened for reading
   * maze or cave information.
   */
  void CloseFile() { istrm_.close(); }

 protected:
  std::ifstream istrm_; /**< The input file stream. */
  int sz_;              /**< The size of the maze/cave. */
};

#endif  // BASE_LOADER_H_
