#include "MazeLoader.h"

namespace maze {

  std::vector<Ceil> MazeLoader::ReadMaze() {
    int value;
    std::vector<Ceil> maze;
    maze.resize(sz_ * sz_);

    for (std::size_t i = 0; i < maze.size(); ++i) {
        istrm_ >> value;
        maze[i].right = value;
    }


    for (std::size_t i = 0; i < maze.size(); ++i) {
        istrm_ >> value;
        maze[i].bottm = value;
    }

    CloseFile();

    return maze;
  }

} // namespace maze
