#include "camera.hpp"

Camera::Camera(ImplCallback callback) noexcept : implCallback(callback) {
  trackLines.reserve(2); // Reserve space for two track lines (left and right)
}

Vector2D Camera::getVehiclePosition() noexcept {
  // Return the current vehicle position on the track.
  return vehicleLocation;
}

bool Camera::isNoTrackDetected() noexcept {
  // Check if no track lines are detected.
  return trackLines.empty();
}

void Camera::update() {
  // Update the detected track lines by calling the implementation callback.
  std::span<uint16_t> buffer; // This should be replaced with actual image data.
  implCallback(buffer);

  // Assuming the buffer represents one-dimensional buffer (one row) of pixel brightness values
  // Calculate average birghtness
  uint32_t averageBrightness = 0;
  for(auto const &pixel : buffer) {
    averageBrightness += pixel;
  }
  averageBrightness /= static_cast<uint32_t>(buffer.size());

  // Clear previous track lines
  trackLines.clear();

  // Find left track lines based on brightness
  TrackLine leftLine;
  for(size_t i = 0; i < buffer.size() / 2; ++i) {
    if(buffer[i] < averageBrightness) {
      leftLine.width += 1;
      leftLine.location.x = static_cast<int>(i);
    }
  }
  trackLines.push_back(leftLine);

  // Find right track lines based on brightness
  TrackLine rightLine;
  for(size_t i = buffer.size() - 1; i > buffer.size() / 2; --i) {
    if(buffer[i] < averageBrightness) {
      rightLine.width += 1;
      rightLine.location.x = static_cast<int>(i);
    }
  }
  trackLines.push_back(rightLine);

  // Update vehicle location based on the detected track lines
  if(2 == trackLines.size()) {
    vehicleLocation.x = (trackLines[left].location.x + trackLines[right].location.x) / 2;
  }
}
