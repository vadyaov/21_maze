/* Должно быть обеспечено полное покрытие unit-тестами модуля генерации пещер */

#include <gtest/gtest.h>

#include <filesystem>

#include "../model/cave/Cave.h"

using namespace cave;

TEST(cave_load, t1) {
  Cave cave;

  std::string currentWorkingDirectory = std::filesystem::current_path().string();
  std::filesystem::current_path("/home/vadim/Projects/School21/21_maze/src");

  cave.LoadCave("examples/cave_1.txt");

  EXPECT_EQ(cave.Size(), 4);

  std::filesystem::current_path(currentWorkingDirectory);

  std::vector<bool> expected = {0, 1, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 1};
  
  for (std::size_t i = 0; i < cave.Size(); ++i)
    for (std::size_t j = 0; j < cave.Size(); ++j)
      EXPECT_EQ(cave.At(i, j), expected.at(i * cave.Size() + j));
}

TEST(cave_load, t2) {
  Cave cave;

  std::string currentWorkingDirectory = std::filesystem::current_path().string();
  std::filesystem::current_path("/home/vadim/Projects/School21/21_maze/src");

  cave.LoadCave("examples/cave_2.txt");

  std::filesystem::current_path(currentWorkingDirectory);

  EXPECT_EQ(cave.Size(), 10);

  std::vector<bool> expected = {1, 0, 1, 0, 0, 0, 0, 1, 1, 0,
                                0, 0, 1, 1, 0, 0, 0, 0, 0, 1,
                                0, 0, 1, 0, 1, 0, 1, 1, 0, 1,
                                0, 1, 1, 1, 1, 1, 1, 0, 0, 0,
                                0, 0, 0, 1, 1, 0, 0, 1, 1, 1,
                                0, 1, 0, 1, 0, 1, 0, 0, 0, 0,
                                1, 1, 0, 0, 0, 0, 0, 1, 0, 0,
                                0, 0, 0, 0, 0, 0, 1, 0, 1, 1,
                                1, 0, 0, 0, 0, 1, 1, 0, 0, 0,
                                0, 1, 1, 0, 0, 1, 1, 0, 0, 0};

  
  for (std::size_t i = 0; i < cave.Size(); ++i)
    for (std::size_t j = 0; j < cave.Size(); ++j)
      EXPECT_EQ(cave.At(i, j), expected.at(i * cave.Size() + j));
}

TEST(cave_init, t1) {
  Cave cave;
  const int size = 10;
  const double probability = 0.75;

  cave.Init(size, probability);

  EXPECT_EQ(cave.Size(), 10);
}

TEST(cave_init, t2) {
  Cave cave;
  const int size = 50;
  const double probability = 0.48;

  cave.Init(size, probability);

  EXPECT_EQ(cave.Size(), 50);
}

TEST(cave_simulation, t1) {
  Cave cave;

  std::string currentWorkingDirectory = std::filesystem::current_path().string();
  std::filesystem::current_path("/home/vadim/Projects/School21/21_maze/src");

  cave.LoadCave("examples/cave_2.txt");

  std::filesystem::current_path(currentWorkingDirectory);

  for (int i = 0; i < 20; ++i)
    cave.NextGeneration(4, 3);

  /* for (std::size_t i = 0; i < cave.Size(); ++i) */
  /*   for (std::size_t j = 0; j < cave.Size(); ++j) */
  /*     std::cout << cave.At(i, j) << ", "; */

  std::vector<bool> expected = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                                1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                                1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                                1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                                1, 1, 1, 1, 1, 1, 0, 0, 1, 1,
                                1, 1, 0, 0, 0, 0, 0, 0, 0, 1,
                                1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                                1, 0, 0, 0, 0, 0, 0, 0, 1, 1,
                                1, 1, 0, 0, 0, 1, 1, 1, 1, 1,
                                1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

  for (std::size_t i = 0; i < cave.Size(); ++i)
    for (std::size_t j = 0; j < cave.Size(); ++j)
      EXPECT_EQ(cave.At(i, j), expected.at(i * cave.Size() + j));
}

TEST(cave_simulation, t2) {
  Cave cave;

  std::string currentWorkingDirectory = std::filesystem::current_path().string();
  std::filesystem::current_path("/home/vadim/Projects/School21/21_maze/src");

  cave.LoadCave("examples/cave_3.txt");

  std::filesystem::current_path(currentWorkingDirectory);

  for (int i = 0; i < 20; ++i)
    cave.NextGeneration(6, 1);

  std::vector<bool> expected = {1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1,
                                0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0,
                                1, 1, 0, 0, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1,
                                1, 1, 0, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1,
                                1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0,
                                1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0,
                                1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0,
                                0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 0,
                                0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1,
                                1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1,
                                1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1,
                                1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0,
                                1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1,
                                1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1,
                                1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1,
                                1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0,
                                0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1,
                                1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1,
                                1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1,
                                1, 1, 0, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1
                                };
  EXPECT_EQ(expected.size(), cave.Size() * cave.Size());

  for (std::size_t i = 0; i < cave.Size(); ++i)
    for (std::size_t j = 0; j < cave.Size(); ++j)
      EXPECT_EQ(cave.At(i, j), expected.at(i * cave.Size() + j));
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
