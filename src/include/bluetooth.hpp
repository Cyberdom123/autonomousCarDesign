#pragma once

namespace Bluetooth {

/**
 * @brief Initializes the Bluetooth service and starts advertising.
 */
void init(void);

/**
 * @brief Reads the speed of the motors.
 */
void readMotorsSpeed(void);

/**
 * @brief Reads the vehicle's location.
 */
void readVehicleLocation(void);

/**
 * @brief Reads the detected objects.
 */
void readDetectedObjects(void);

} // namespace Bluetooth
