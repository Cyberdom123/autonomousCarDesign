#include <bluetooth.hpp>
#include <camera.hpp>
#include <control_loop.hpp>
#include <motors.hpp>
#include <stdio.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/kernel.h>

int main(void) {
  Bluetooth::init();

  Motors motors(
      [](Motors::Orientation orientation, int32_t power) {
        // Set motor power based on orientation and power level
        if(orientation == Motors::Orientation::Left) {
          printf("Setting left motor power to %d\n", power);
        } else {
          printf("Setting right motor power to %d\n", power);
        }
      },
      [](void) -> Vector2D {
        // Get current speed of the motors
        return Vector2D{0, 0}; // Placeholder for actual speed retrieval logic
      });

  LIDAR lidar([](std::vector<Obstacle> &detectedObstacles) {});

  Camera camera([](std::span<uint16_t> &buffer) {
    // Simulate capturing image data
    static uint16_t testData[] = {10, 10, 0, 0, 0, 0, 0, 10, 10, 10};
    buffer = std::span<uint16_t>(testData, sizeof(testData) / sizeof(testData[0]));
  });

  ControlLoop controlLoop(motors, camera, lidar);
  controlLoop.enable();

  while(1) {
    controlLoop.process(k_uptime_get());

    // Sleep
    Bluetooth::readMotorsSpeed();
    Bluetooth::readVehicleLocation();
    Bluetooth::readDetectedObjects();

    k_msleep(100);
  }

  return 0;
}
