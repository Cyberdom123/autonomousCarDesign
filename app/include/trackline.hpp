#pragma once
#include "detected_object.hpp"
#include <string>

class TrackLine : public DetectedObject {
public:
  /// Width of the track line in pixels.
  int width;
};
