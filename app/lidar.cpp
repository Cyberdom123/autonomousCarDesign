#include "lidar.hpp"

std::vector<Obstacle> const &LIDAR::getDetectedObjects() noexcept { return detectedObstacles; }

size_t LIDAR::getNumberOfDetectedObjects() noexcept { return detectedObstacles.size(); }

void LIDAR::update() noexcept {
  // Simulate the process of detecting obstacles
  detectedObstacles.clear();

  getObstacles(detectedObstacles); // Get the detected obstacles from the callback

  filter(); // Filter the detected obstacles
}

void LIDAR::filter() {
  std::vector<Obstacle> filteredObstacles;

  static constexpr int maxDistance = 1000;

  for(auto const &obstacle : detectedObstacles) {
    if(obstacle.distance < maxDistance) { // Example condition to filter out obstacles that are too far away
      filteredObstacles.push_back(obstacle);
    }
  }

  detectedObstacles = std::move(filteredObstacles); // Update the detected obstacles with the filtered ones
}
