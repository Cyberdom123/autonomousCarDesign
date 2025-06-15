add_library(application camera.cpp control_loop.cpp lidar.cpp motors.cpp vector2D.cpp)

target_include_directories(application PUBLIC include)
