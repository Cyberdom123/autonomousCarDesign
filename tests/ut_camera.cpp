#include "camera.hpp"
#include "trackline.hpp"
#include <gtest/gtest.h>

TEST(CameraTest, Constructor) {
  Camera camera([](std::span<uint16_t> &buffer) {
    // Empty span for the test
    buffer = std::span<uint16_t>();
  });
}

TEST(CameraTest, GetVehiclePosition) {
  Camera camera([](std::span<uint16_t> &buffer) {
    // Empty span for the test
    buffer = std::span<uint16_t>();
  });

  Vector2D position = camera.getVehiclePosition();
  EXPECT_EQ(position.x, 0);
  EXPECT_EQ(position.y, 0);
}

TEST(CameraTest, IsNoTrackDetected) {
  Camera camera([](std::span<uint16_t> &buffer) {
    // Empty span for the test
    buffer = std::span<uint16_t>();
  });

  EXPECT_TRUE(camera.isNoTrackDetected());
}

TEST(CameraTest, Update) {
  Camera camera([](std::span<uint16_t> &buffer) {
    // Empty span for the test
    uint16_t testData[] = {10, 10, 0, 0, 0, 0, 0, 10, 10, 10};
    buffer = std::span<uint16_t>(testData, sizeof(testData) / sizeof(testData[0]));
  });

  // Call update to simulate periodic update
  camera.update();

  // Check if the vehicle position remains unchanged
  Vector2D position = camera.getVehiclePosition();
  EXPECT_NE(position.x, 0);
  EXPECT_EQ(position.y, 0);
}
