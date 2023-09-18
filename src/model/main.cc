#include "maze.h"

#include <iostream>

int main() {
  try {
  maze::Maze maze("../examples/maze_2.txt");
  maze.print();
  } catch (const std::exception& e) {
    std::cout << e.what() << std::endl;
  }
  return 0;
}
