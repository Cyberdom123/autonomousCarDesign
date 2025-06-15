#pragma once
#include "vector2D.hpp"

class DetectedObject {
public:
  /// Unique identifier for the detected object.
  int id = 0;

  /// Location of the detected object in 2D space.
  Vector2D location;

  /// Certainty of the detection, ranging from 0.0 (no certainty) to 1.0 (high certainty).
  double certainty = 1.0;

  /// Marking a destructor as virtual ensures that when you delete an object through a pointer to a base class, the destructor of the derived class is
  /// called as well.
  virtual ~DetectedObject() = default;
};
