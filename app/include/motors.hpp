#pragma once
#include "vector2D.hpp"
#include <cstdint>
#include <functional>

class Motors {
public:
  /// Motor orientation on the vehicle.
  enum class Orientation {
    Left,
    Right,
  };

  /**
   * Callback type for setting motor power to be implemented by the user.
   *
   * @param orientation The orientation of the motor (Left or Right).
   * @param power The power level to set for the motor, in the range of -100 to 100.
   */
  typedef std::function<void(Orientation orientation, int32_t power)> ImplCallbackPower;

  /**
   * Callback type for getting motor speed to be implemented by the user.
   *
   * @param orientation The orientation of the motor (Left or Right).
   * @param speed The speed of the motor.
   */
  typedef std::function<Vector2D(void)> ImplCallbackSpeed;

  /**
   * Constructor for the Motors class.
   *
   * @param ImplCallback A callback function that sets the motor power.
   */
  Motors(ImplCallbackPower implCallbackPower, ImplCallbackSpeed implCallbackSpeed)
      : setMotorPower(implCallbackPower), getMotorSpeed(implCallbackSpeed) {}

  /**
   * Function used to set the power of the motors.
   *
   * @param power A Vector2D representing the power for the left and right motors.
   *              The x-coordinate is for the left motor and the y-coordinate is for the right motor.
   */
  void setMotorsPower(Vector2D power) noexcept;

  /**
   * Function used to get the current power of the motors.
   */
  Vector2D getMotorsSpeed() noexcept;

  void process() noexcept;

private:
  /// Current power of the motors.
  Vector2D motorsPower;

  /// Current speed of the motors.
  Vector2D motorsSpeed;

  /// Callback function to set the motor power.
  ImplCallbackPower setMotorPower;

  /// Callback function to get the motor speed.
  ImplCallbackSpeed getMotorSpeed;
};
