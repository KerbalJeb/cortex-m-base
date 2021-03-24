add_subdirectory(test)

add_library(peripheral_driver src/gpio.cpp)
target_include_directories(peripheral_driver
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/inc)