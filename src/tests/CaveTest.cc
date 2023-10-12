/* Должно быть обеспечено полное покрытие unit-тестами модуля генерации пещер */

#include <gtest/gtest.h>

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
