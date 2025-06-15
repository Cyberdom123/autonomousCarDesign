#include "motors.hpp"
#include <algorithm>

void Motors::setMotorsPower(Vector2D power) noexcept {
  static constexpr int32_t maxPower = 100;
  static constexpr int32_t minPower = -100;
  std::clamp(power.x, minPower, maxPower);
  std::clamp(power.y, minPower, maxPower);

  // Save the power of the motors.
  motorsPower = power;
}

Vector2D Motors::getMotorsSpeed() noexcept { return motorsSpeed; }

void Motors::process() noexcept {
  // Set the power of the motors.
  setMotorPower(Orientation::Left, motorsPower.x);
  setMotorPower(Orientation::Right, motorsPower.y);

  // Update the speed of the motors.
  motorsSpeed = getMotorSpeed();
}
