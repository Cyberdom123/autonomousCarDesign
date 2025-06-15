#include "control_loop.hpp"

void ControlLoop::process(microseconds now) noexcept {
  if(!areMotorsEnabled) {
    return;
  }

  static constexpr microseconds updateInterval = microseconds(1000); // 1 ms
  if(now - lastUpdateTime < updateInterval) {
    return;
  }

  motors.process();
  lidar.update();
  camera.update();

  lastUpdateTime = now;
}

void ControlLoop::disable() noexcept {
  areMotorsEnabled = false;
  motors.setMotorsPower(Vector2D(0, 0)); // Stop the motors
}

void ControlLoop::enable() noexcept {
  areMotorsEnabled = true;
  lastUpdateTime = microseconds(0); // Reset the last update time
}

Vector2D ControlLoop::getVehicleSpeed() noexcept { return motors.getMotorsSpeed(); }

void ControlLoop::setTargetSpeed(Vector2D targetSpeed) noexcept {
  if(!areMotorsEnabled) {
    return;
  }

  // Set the target speed for the motors
  motors.setMotorsPower(targetSpeed);
}
