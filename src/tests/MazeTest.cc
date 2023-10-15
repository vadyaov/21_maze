#include <gtest/gtest.h>
#include <filesystem>

#include "../model/maze/Maze.h"

using namespace maze;

TEST(maze_load, t1) {
  Maze m;

  std::string currentWorkingDirectory = std::filesystem::current_path().string();

  std::filesystem::current_path("/home/vadim/Projects/School21/21_maze/src");

  m.LoadMaze("examples/maze_1.txt");

  std::filesystem::current_path(currentWorkingDirectory);

  const std::vector<Ceil>& loaded = m.GetCeils();
  const std::vector<Ceil> expected = {{0, 1}, {0, 0}, {0, 1}, {1, 0},
                                      {1, 0}, {0, 0}, {1, 1}, {1, 0},
                                      {0, 1}, {1, 1}, {0, 0}, {1, 1},
                                      {0, 1}, {0, 1}, {0, 1}, {1, 1}};

  EXPECT_EQ(loaded.size(), expected.size());

  for (std::size_t i = 0; i < loaded.size(); ++i) {
    EXPECT_EQ(loaded[i].right, expected[i].right);
    EXPECT_EQ(loaded[i].bottm, expected[i].bottm);
  }

}

TEST(maze_load, t2) {
  Maze m;

  std::string currentWorkingDirectory = std::filesystem::current_path().string();

  std::filesystem::current_path("/home/vadim/Projects/School21/21_maze/src");

  m.LoadMaze("examples/maze_3.txt");

  std::filesystem::current_path(currentWorkingDirectory);

  const std::vector<Ceil>& loaded = m.GetCeils();
  const std::vector<Ceil> expected = {{1, 0}, {1, 0}, {0, 0}, {0, 1}, {0, 0}, {0, 1}, {1, 0}, {0, 0}, {0, 1}, {1, 0},
                                      {0, 0}, {1, 1}, {0, 1}, {1, 0}, {1, 0}, {1, 0}, {1, 0}, {1, 0}, {1, 0}, {1, 0},
                                      {1, 0}, {0, 0}, {0, 0}, {1, 1}, {0, 1}, {1, 1}, {1, 0}, {0, 1}, {1, 0}, {1, 0},
                                      {1, 0}, {1, 0}, {1, 1}, {0, 1}, {0, 1}, {0, 1}, {1, 0}, {1, 0}, {0, 0}, {1, 0},
                                      {0, 0}, {1, 0}, {0, 0}, {1, 1}, {0, 0}, {0, 1}, {1, 1}, {0, 0}, {1, 0}, {1, 0},
                                      {1, 0}, {0, 1}, {1, 1}, {0, 0}, {1, 1}, {0, 0}, {0, 1}, {1, 1}, {1, 1}, {1, 0},
                                      {1, 1}, {0, 1}, {1, 0}, {1, 0}, {1, 0}, {0, 1}, {0, 1}, {1, 0}, {0, 0}, {1, 1},
                                      {0, 0}, {0, 1}, {0, 1}, {0, 1}, {0, 1}, {1, 0}, {0, 1}, {1, 0}, {1, 0}, {1, 0},
                                      {1, 0}, {1, 0}, {0, 1}, {0, 1}, {1, 0}, {0, 1}, {0, 1}, {1, 1}, {0, 1}, {1, 0},
                                      {0, 1}, {0, 1}, {0, 1}, {1, 1}, {0, 1}, {0, 1}, {0, 1}, {0, 1}, {0, 1}, {1, 1}
  };

  EXPECT_EQ(loaded.size(), expected.size());

  for (std::size_t i = 0; i < loaded.size(); ++i) {
    EXPECT_EQ(loaded[i].right, expected[i].right);
    EXPECT_EQ(loaded[i].bottm, expected[i].bottm);
  }

}

TEST(maze_solution, t1) {
  Maze m;

  std::string currentWorkingDirectory = std::filesystem::current_path().string();

  std::filesystem::current_path("/home/vadim/Projects/School21/21_maze/src");

  m.LoadMaze("examples/maze_3.txt");

  std::filesystem::current_path(currentWorkingDirectory);

  Maze::Coord start_point = {0, 0};
  Maze::Coord end_point = {1, 5};

  auto solution = m.FindSolution(start_point, end_point);
  std::vector<Maze::Coord> expected_solution = {{2, 5}, {2, 4}, {1, 4},
    {0, 4}, {0, 3}, {0, 2}, {1, 2}, {1, 3}, {2, 3}, {2, 2}, {2, 1}, {3, 1}, {4, 1}, {4, 0},
    {3, 0}, {2, 0}, {1, 0}, start_point};

  EXPECT_EQ(solution.size(), expected_solution.size());

  for (std::size_t i = 0; i < solution.size(); ++i)
    EXPECT_EQ(solution[i], expected_solution[i]);

}

TEST(maze_solution, t2) {
  Maze m;

  std::string currentWorkingDirectory = std::filesystem::current_path().string();

  std::filesystem::current_path("/home/vadim/Projects/School21/21_maze/src");

  m.LoadMaze("examples/maze_3.txt");

  std::filesystem::current_path(currentWorkingDirectory);

  Maze::Coord start_point = {8, 2};
  Maze::Coord end_point = {1, 5};

  auto solution = m.FindSolution(start_point, end_point);
  std::vector<Maze::Coord> expected_solution = {{2, 5}, {2, 4}, {1, 4},
    {0, 4}, {0, 5}, {0, 6}, {1, 6}, {2, 6}, {3, 6}, {4, 6}, {4, 5}, {4, 4}, {5, 4}, {5, 3},
    {6, 3}, {7, 3}, {7, 4}, {7, 5}, {8, 5}, {8, 6}, {8, 7}, {7, 7}, {6, 7}, {6, 6}, {6, 5},
    {5, 5}, {5, 6}, {5, 7}, {4, 7}, {4, 8}, {3, 8}, {3, 9}, {4, 9}, {5, 9}, {6, 9}, {6, 8},
    {7, 8}, {8, 8}, {8, 9}, {9, 9}, {9, 8}, {9, 7}, {9, 6}, {9, 5}, {9, 4}, {8, 4}, {8, 3},
    start_point};

  EXPECT_EQ(solution.size(), expected_solution.size());

  for (std::size_t i = 0; i < solution.size(); ++i)
    EXPECT_EQ(solution[i], expected_solution[i]);

}

TEST(maze_solution, t3) {
  Maze m;

  std::string currentWorkingDirectory = std::filesystem::current_path().string();

  std::filesystem::current_path("/home/vadim/Projects/School21/21_maze/src");

  m.LoadMaze("examples/maze_2.txt");

  std::filesystem::current_path(currentWorkingDirectory);

  Maze::Coord start_point = {1, 1};
  Maze::Coord end_point = {4, 2};

  auto solution = m.FindSolution(start_point, end_point);
  std::vector<Maze::Coord> expected_solution = {{4, 1}, {5, 1}, {5, 2},
    {5, 3}, {5, 4}, {5, 5}, {4, 5}, {4, 6}, {3, 6}, {3, 5}, {3, 4}, {4, 4}, {4, 3}, {3, 3},
    {3, 2}, {3, 1}, {2, 1}, {2, 2}, {1, 2}, {0, 2}, {0, 1}, {0, 0}, {1, 0}, start_point};

  EXPECT_EQ(solution.size(), expected_solution.size());

  for (std::size_t i = 0; i < solution.size(); ++i)
    EXPECT_EQ(solution[i], expected_solution[i]);

}

TEST(maze_solution, t4) {
  Maze m;

  std::string currentWorkingDirectory = std::filesystem::current_path().string();

  std::filesystem::current_path("/home/vadim/Projects/School21/21_maze/src");

  m.LoadMaze("examples/maze_2.txt");

  std::filesystem::current_path(currentWorkingDirectory);

  Maze::Coord start_point = {9, 0};
  Maze::Coord end_point = {7, 8};

  auto solution = m.FindSolution(start_point, end_point);
  std::vector<Maze::Coord> expected_solution = {{7, 9}, {8, 9}, {8, 8},
    {8, 7}, {7, 7}, {6, 7}, {6, 6}, {6, 5}, {7, 5}, {8, 5}, {9, 5}, {9, 4}, {8, 4}, {8, 3},
    {8, 2}, {8, 1}, {9, 1}, start_point};

  EXPECT_EQ(solution.size(), expected_solution.size());

  for (std::size_t i = 0; i < solution.size(); ++i)
    EXPECT_EQ(solution[i], expected_solution[i]);

}

TEST(maze_solution, t5) {
  Maze m;

  std::string currentWorkingDirectory = std::filesystem::current_path().string();

  std::filesystem::current_path("/home/vadim/Projects/School21/21_maze/src");

  m.LoadMaze("examples/maze_4.txt");

  std::filesystem::current_path(currentWorkingDirectory);

  Maze::Coord start_point = {18, 3};
  Maze::Coord end_point = {15, 19};

  auto solution = m.FindSolution(start_point, end_point);
  std::vector<Maze::Coord> expected_solution = {{14, 19}, {14, 18}, {15, 18},
    {15, 17}, {14, 17}, {14, 16}, {15, 16}, {15, 15}, {14, 15}, {14, 14}, {15, 14},
    {16, 14}, {16, 15}, {16, 16}, {16, 17}, {16, 18}, {16, 19}, {17, 19}, {18, 19},
    {18, 18}, {18, 17}, {18, 16}, {18, 15}, {18, 14}, {18, 13}, {18, 12}, {18, 11},
    {18, 10}, {19, 10}, {19, 9}, {19, 8}, {18, 8}, {17, 8}, {16, 8}, {15, 8}, {14, 8},
    {13, 8}, {12, 8}, {12, 7}, {12, 6}, {12, 5}, {12, 4}, {12, 3}, {12, 2}, {12, 1},
    {12, 0}, {13, 0}, {14, 0}, {15, 0}, {16, 0}, {17, 0}, {18, 0}, {19, 0},
    {19, 1}, {18, 1}, {17, 1}, {16, 1}, {15, 1}, {14, 1}, {13, 1}, {13, 2}, {14, 2},
    {15, 2}, {15, 3}, {15, 4}, {15, 5}, {15, 6}, {16, 6}, {17, 6}, {18, 6},
    {18, 5}, {17, 5}, {16, 5}, {16, 4}, {16, 3}, {17, 3}, {17, 4}, {18, 4}, start_point};

  EXPECT_EQ(solution.size(), expected_solution.size());

  for (std::size_t i = 0; i < solution.size(); ++i)
    EXPECT_EQ(solution[i], expected_solution[i]);

}

TEST(maze_solution, t6) {
  Maze m;

  std::string currentWorkingDirectory = std::filesystem::current_path().string();

  std::filesystem::current_path("/home/vadim/Projects/School21/21_maze/src");

  m.LoadMaze("examples/maze_4.txt");

  std::filesystem::current_path(currentWorkingDirectory);

  Maze::Coord start_point = {15, 19};
  Maze::Coord end_point = {1, 5};

  auto solution = m.FindSolution(start_point, end_point);
  std::vector<Maze::Coord> expected_solution = {{0, 5}, {0, 6}, {1, 6}, {1, 7}, {0, 7},
    {0, 8}, {0, 9}, {1, 9}, {1, 8}, {2, 8}, {2, 9}, {2, 10}, {3, 10}, {3, 9}, {4, 9},
    {5, 9}, {6, 9}, {6, 8}, {6, 7}, {6, 6}, {6, 5}, {6, 4}, {7, 4}, {7, 5}, {8, 5},
    {9, 5}, {10, 5}, {11, 5}, {12, 5}, {12, 6}, {12, 7}, {12, 8}, {13, 8}, {14, 8},
    {15, 8}, {16, 8}, {17, 8}, {18, 8}, {19, 8}, {19, 9}, {19, 10}, {18, 10}, {18, 11},
    {18, 12}, {18, 13}, {18, 14}, {18, 15}, {18, 16}, {18, 17}, {18, 18}, {18, 19},
    {17, 19}, {16, 19}, {16, 18}, {16, 17}, {16, 16}, {16, 15}, {16, 14}, {15, 14},
    {14, 14}, {14, 15}, {15, 15}, {15, 16}, {14, 16}, {14, 17}, {15, 17}, {15, 18},
    {14, 18}, {14, 19}, start_point};

  EXPECT_EQ(solution.size(), expected_solution.size());

  for (std::size_t i = 0; i < solution.size(); ++i)
    EXPECT_EQ(solution[i], expected_solution[i]);

}
