#include "mazeloader.h"

namespace maze {

  std::vector<Ceil> MazeLoader::ReadMaze() {
    int value;
    std::vector<Ceil> maze;
    maze.resize(sz_ * sz_);
    for (std::size_t i = 0; i < maze.size(); ++i) {
        istrm_ >> value;
        maze[i].GetRight() = value;
    }

    for (std::size_t i = 0; i < maze.size(); ++i) {
        istrm_ >> value;
        maze[i].GetDown() = value;
    }

    CloseFile();

    return maze;
  }

} // namespace maze
