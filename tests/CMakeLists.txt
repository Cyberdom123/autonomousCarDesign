add_executable(
  application_ut
  # test sources
  ${CMAKE_CURRENT_LIST_DIR}/ut_camera.cpp ${CMAKE_CURRENT_LIST_DIR}/ut_motors.cpp
  ${CMAKE_CURRENT_LIST_DIR}/ut_lidar.cpp
)

FetchContent_MakeAvailable(googletest)

target_include_directories(application_ut PRIVATE ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(application_ut PRIVATE application GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(application_ut)
