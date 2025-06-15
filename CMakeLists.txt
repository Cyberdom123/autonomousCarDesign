cmake_minimum_required(VERSION 3.20)

# Zephyr must be initialized before the project() command
if (NOT UNIT_TESTING)
  set(ENV{VIRTUAL_ENV} ${ZEPHYR_ENV})
  find_package(Python3)

  list(APPEND SOC_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
  list(APPEND BOARD_ROOT ${CMAKE_CURRENT_SOURCE_DIR})

  find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
endif ()

project(nxp-cup VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)

option(UNIT_TESTING "Enable unit testing" OFF)

include(${CMAKE_CURRENT_SOURCE_DIR}/requirements.cmake)

add_subdirectory(app)

if (UNIT_TESTING)
  enable_testing()
  add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tests)
else ()
  target_sources(app PRIVATE src/main.cpp src/bluetooth.cpp)

  target_include_directories(app PRIVATE src/include)

  target_link_libraries(app PRIVATE application)
  # Assigment to use the same compile options as the zephyr application
  target_link_libraries(application PRIVATE app)
endif ()
