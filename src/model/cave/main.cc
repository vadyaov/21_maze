#include "cave.h"

using namespace cave;

int main() {
  Cave cave;
  cave.LoadCave("../../examples/cave_1.txt");
  cave.print_cave();
  return 0;
}
