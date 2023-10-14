#ifndef BASE_LOADER_H_
#define BASE_LOADER_H_

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

class BaseLoader {
  public:
    BaseLoader() : istrm_{}, sz_{0} {}

    void OpenFile(const std::string& path) {
      std::cout << "PATH: " << path << std::endl;
      istrm_.open(path);
      if (!istrm_.is_open())
        throw std::invalid_argument("Incorrect path.");

      int rows, columns;
      istrm_ >> rows >> columns;

      if (rows != columns || rows > 50 || rows < 2)
        throw std::invalid_argument("Incorrect size.");

      sz_ = rows;
    }

    void CloseFile() {
      istrm_.close();
    }

  protected:
    std::ifstream istrm_;
    int sz_;
};

#endif // BASE_LOADER_H_
