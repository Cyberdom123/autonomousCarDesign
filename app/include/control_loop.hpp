#pragma once
#include "camera.hpp"
#include "lidar.hpp"
#include "motors.hpp"
#include "vector2D.hpp"
#include <chrono>

using namespace std::chrono;

class ControlLoop {
private:
  /// flag to indicate if the control loop is enabled
  bool areMotorsEnabled = false;

  /// vehicle motors instance
  Motors motors;

  /// LIDAR sensor instance
  LIDAR lidar;

  /// Camera instance
  Camera camera;

  /// Last update time of the control loop
  microseconds lastUpdateTime = microseconds(0);

public:
  /**
   * Constructor for the ControlLoop class.
   * Initializes the control loop with the provided motor, LIDAR, and camera instances.
   *
   * @param motors The Motors instance to control the vehicle's motors.
   * @param lidar The LIDAR instance for obstacle detection.
   * @param camera The Camera instance for vehicle tracking.
   */
  ControlLoop(Motors motors, LIDAR lidar, Camera camera) noexcept : motors(std::move(motors)), lidar(std::move(lidar)), camera(std::move(camera)) {}

  /**
   * Process the control loop logic.
   * This method is responsible for updating the vehicle's speed and direction
   *
   * @param now The current time in microseconds.
   */
  void process(microseconds now) noexcept;

  /**
   * Disable or enable the control loop.
   */
  void disable() noexcept;

  /**
   * Enable the control loop.
   */
  void enable() noexcept;

  /**
   * Get current vehicle speed.
   *
   * @return The current speed of the vehicle as a Vector2D.
   */
  Vector2D getVehicleSpeed() noexcept;

  /**
   * Set the target speed for the vehicle.
   * This method updates the target speed that the control loop will try to achieve.
   *
   * @param targetSpeed The desired speed as a Vector2D.
   */
  void setTargetSpeed(Vector2D targetSpeed) noexcept;
};
