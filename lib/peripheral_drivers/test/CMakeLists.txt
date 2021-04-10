
if (NOT CMAKE_CROSSCOMPILING)
  project(unit_tests)

  add_executable (DriverTests gpio_test.cpp spi_test.cpp)


  target_link_libraries (DriverTests
                         PRIVATE
                         gtest_main
                         gmock_main
                         peripheral_drivers
                         DeviceCMSIS
                         FreeRTOS
                         fff
                         )
  add_test(NAME driver_unit_tests COMMAND ${CMAKE_CURRENT_BINARY_DIR}/DriverTests)
endif ()
