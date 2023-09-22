#include "../controller/controller.h"

#include <iostream>

int main() {
  try {
  maze::Controller ctr;
  ctr.ReadMaze("../examples/maze_1.txt");
  ctr.print();
  } catch (const std::exception& e) {
    std::cout << e.what() << std::endl;
  }
  return 0;
}
