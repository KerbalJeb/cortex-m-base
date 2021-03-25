
if (NOT CMAKE_CROSSCOMPILING)
  project(unit_tests)

  add_subdirectory(mocks)
  add_executable (DriverTests gpio_test.cpp)


  target_link_libraries (DriverTests
                         PRIVATE
                         gtest_main
                         gmock_main
                         CMSIS_Mocks
                         peripheral_drivers
                         )
  add_test(NAME unit COMMAND ${CMAKE_CURRENT_BINARY_DIR}/DriverTests)
endif ()
