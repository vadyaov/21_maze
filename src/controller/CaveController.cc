#include "CaveController.h"

namespace cave {

void Controller::ReadCave(const std::string& path) {
  c.LoadCave(path);
}

} // namespcae cave
