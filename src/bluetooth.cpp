#include "bluetooth.hpp"
#include <bluetooth/services/lbs.h>
#include <bluetooth/services/nsms.h>
#include <cstring>
#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/conn.h>
#include <zephyr/bluetooth/gatt.h>
#include <zephyr/bluetooth/hci.h>
#include <zephyr/bluetooth/uuid.h>

enum {
  BUFFER_SIZE = 64,
};

BT_NSMS_DEF(nsmsVelocity, "Motors velcity", false, "Unknown", BUFFER_SIZE);
BT_NSMS_DEF(nsmsDetectedObjects, "Detected objects", false, "Unknown", BUFFER_SIZE);
BT_NSMS_DEF(nsmsVehicleLocation, "Vehicle location", false, "Unknown", BUFFER_SIZE);

#define DEVICE_NAME CONFIG_BT_DEVICE_NAME
#define DEVICE_NAME_LEN (sizeof(DEVICE_NAME) - 1)

static const struct bt_data ad[] = {
    BT_DATA_BYTES(BT_DATA_FLAGS, (BT_LE_AD_GENERAL | BT_LE_AD_NO_BREDR)),
};

static const struct bt_data sd[] = {
    BT_DATA(BT_DATA_NAME_COMPLETE, CONFIG_BT_DEVICE_NAME, sizeof(CONFIG_BT_DEVICE_NAME) - 1),
};

void Bluetooth::init(void) {
  // Initialize Bluetooth stack
  int err = bt_enable(NULL);
  if(err) {
    printk("Bluetooth init failed (err %d)\n", err);
    return;
  }

  printk("Bluetooth initialized\n");

  // Set up advertising
  err = bt_le_adv_start(BT_LE_ADV_CONN, ad, ARRAY_SIZE(ad), sd, ARRAY_SIZE(sd));
  if(err) {
    printk("Advertising failed to start (err %d)\n", err);
    return;
  }

  printk("Advertising started\n");
}

void Bluetooth::readMotorsSpeed() {
  char buffer[BUFFER_SIZE];
  snprintf(buffer, sizeof(buffer), "Motors speed: %d, %d", 10, 20);

  int err = bt_nsms_set_status(&nsmsVelocity, buffer);
  if(err) {
    printk("Failed to read motors speed (err %d)\n", err);
  }
}

void Bluetooth::readVehicleLocation() {
  char buffer[BUFFER_SIZE];
  snprintf(buffer, sizeof(buffer), "Vehicle location: %d %d", 50, 100);

  int err = bt_nsms_set_status(&nsmsVehicleLocation, buffer);
  if(err) {
    printk("Failed to read vehicle location (err %d)\n", err);
  }
}

void Bluetooth::readDetectedObjects() {
  char buffer[BUFFER_SIZE];
  snprintf(buffer, sizeof(buffer), "Detected objects: %s, %s", "Obstacle1", "Obstacle2");

  int err = bt_nsms_set_status(&nsmsDetectedObjects, buffer);
  if(err) {
    printk("Failed to read detected objects (err %d)\n", err);
  }
}
