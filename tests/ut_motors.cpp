#include "motors.hpp"
#include <gtest/gtest.h>

TEST(MotorsTest, Constructor) {
  Motors motors(
      [](Motors::Orientation orientation, int32_t power) {
        // Empty callback for the test
        std::ignore = orientation;
        std::ignore = power;
      },
      []() -> Vector2D { return Vector2D{0, 0}; });
}
