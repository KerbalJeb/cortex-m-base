add_subdirectory(test)

set(PORT_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/portable/st/f0)

add_library(peripheral_drivers
    ${PORT_SRC_DIR}/gpio.cpp
    ${PORT_SRC_DIR}/spi.cpp
)

target_include_directories(peripheral_drivers
        PUBLIC
        ${PORT_SRC_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/inc)

target_link_libraries(peripheral_drivers PRIVATE DeviceCMSIS FreeRTOS)

