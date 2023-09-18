#ifndef MAZE_H_
#define MAZE_H_

#include <iostream>

#include <vector>
#include <string>

namespace maze {
  class Maze {
    public:
      Maze() {}
      Maze(const std::string&);
      // or mb use LoadMaze because of Generation Ideal Mazes next

      void print() {
        std::cout << v_walls_.size() << ' ' << h_walls_.size() << std::endl;

        print_array(v_walls_);
        print_array(h_walls_);
      }

    private:
      std::vector<std::vector<bool>> v_walls_;
      std::vector<std::vector<bool>> h_walls_;

      void print_array(const std::vector<std::vector<bool>>& arr) {
        for (const auto& i : arr) {
          for (int j : i)
            std::cout << j << ' ';
          std::cout << std::endl;
        }
        std::cout << std::endl;
      }
  };
} // namespace s21

#endif // MAZE_H_
