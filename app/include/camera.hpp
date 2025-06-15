#pragma once
#include "trackline.hpp"
#include "vector2D.hpp"
#include <cstdint>
#include <functional>
#include <span>
#include <vector>

class Camera {

public:
  /**
   * Callback type for the camera to be implemented by the user.
   *
   * @param buffer a span of uint8_t representing the raw image data captured by the camera.
   */
  typedef std::function<void(std::span<uint16_t> &buffer)> ImplCallback;

  /**
   * Constructor for the Camera class.
   * This constructor initializes the camera with a callback function that will be called
   * periodically to process the captured image data.
   *
   * @param callback A function that will be called to capture image data.
   */
  Camera(ImplCallback callback) noexcept;

  /**
   * Function for getting the vehicle position on the track.
   *
   * @return Vector2D representing the vehicle's position on the track.
   * The position is represented as a 2D vector with x and y coordinates.
   */
  Vector2D getVehiclePosition() noexcept;

  /**
   * Function that returns the detected track lines.
   */
  bool isNoTrackDetected() noexcept;

  /**
   * Function for periodically updating the detected track lines.
   */
  void update();

private:
  enum {
    left = 0, ///< Index for the left track line.
    right = 1 ///< Index for the right track line.
  };

  /// Location of the vehicle on the track.
  Vector2D vehicleLocation;

  /// Detected track lines from the camera.
  std::vector<TrackLine> trackLines;

  /// Implementation callback for the camera.
  ImplCallback implCallback;
};
