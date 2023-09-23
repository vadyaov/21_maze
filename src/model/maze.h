#ifndef MAZE_H_
#define MAZE_H_

#include <iostream>

#include <cmath>
#include <vector>
#include <string>

namespace maze {

  class Ceil {
    public:
      bool IsRight() const noexcept {return r_wall;}
      bool IsDown() const noexcept {return d_wall;}

      bool& GetRight() noexcept {return r_wall;}
      bool& GetDown() noexcept {return d_wall;}

    private:
      bool r_wall;
      bool d_wall;
  };

  class Maze {
    public:

      void LoadMaze(const std::string& path);
      void Generate(std::size_t size);

      /* Getters */
      std::size_t Size() const noexcept;
      const std::vector<Ceil>& GetCeils() const & noexcept;

      /* debug */
      void print() {
        std::cout << "Size = " << ceils_.size() << std::endl;

        for (std::size_t i = 0, j = 1; i < ceils_.size(); ++i, ++j) {
          std::cout << ceils_[i].IsRight() << ' ';
          if (j == std::sqrt(ceils_.size())) {
            std::cout << std::endl;
            j = 0;
          }
        }

        std::cout << std::endl;

        for (std::size_t i = 0, j = 1; i < ceils_.size(); ++i, ++j) {
          std::cout << ceils_[i].IsDown() << ' ';
          if (j == std::sqrt(ceils_.size())) {
            std::cout << std::endl;
            j = 0;
          }
        }

      }

    private:
      std::vector<Ceil> ceils_;
  };
} // namespace maze

#endif // MAZE_H_
