#pragma once
#include <cmath>

class Vector2D {
public:
  /// X coordinate of the vector.
  int x = 0;

  /// Y coordinate of the vector.
  int y = 0;

  /**
   * Function to get magnitude of the vector.
   *
   * @return The magnitude of the vector, calculated as the square root of the sum of squares of its coordinates.
   * The magnitude is calculated using the formula: sqrt(x^2 + y^2).
   */
  double getMagnitude();
};
