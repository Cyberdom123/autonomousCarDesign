#pragma once
#include "detected_object.hpp"

class Obstacle : public DetectedObject {
public:
  /// Distance to the obstacle in centimeters
  int distance = 0;
};
