
if (NOT CMAKE_CROSSCOMPILING)
    add_executable(DriverTests gpio_test.cpp)

    target_link_libraries(DriverTests
        PRIVATE
        gtest_main
        peripheral_driver)
endif ()
