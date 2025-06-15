#pragma once
#include "obstacle.hpp"
#include <functional>
#include <vector>

class LIDAR {
public:
  /**
   * Callback type for the LIDAR sensor to be implemented by the user.
   * This callback is invoked periodically the current state of detected obstacles.
   *
   * @param detectedObstacles A reference to a vector of Obstacle objects.
   */
  typedef std::function<void(std::vector<Obstacle> &detectedObstacles)> ImplCallback;

  /**
   * Constructor for the LIDAR sensor.
   * This constructor initializes the LIDAR sensor with a callback function that will be called
   * periodically to process the detected obstacles.
   */
  LIDAR(ImplCallback callback) : getObstacles(callback) {}

  /**
   * Function for getting the detected obstacles by the LIDAR sensor.
   */
  std::vector<Obstacle> const &getDetectedObjects() noexcept;

  /**
   * Function for getting the number of detected obstacles by the LIDAR sensor.
   *
   * @return The number of detected obstacles.
   */
  size_t getNumberOfDetectedObjects() noexcept;

  /**
   * Function for periodically updating the detected obstacles.
   */
  void update() noexcept;

private:
  /// Detected obstacles from the LIDAR sensor.
  std::vector<Obstacle> detectedObstacles;

  /**
   * Function for filtering the detected obstacles. This function processes detected obstacles to
   * remove duplicates and auto of range obstacles that are too far away.
   */
  void filter();

  /**
   * Callback function for the LIDAR sensor.
   */
  ImplCallback getObstacles;
};
