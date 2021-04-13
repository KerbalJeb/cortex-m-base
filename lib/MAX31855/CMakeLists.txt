add_library(MAX31855 MAX31855.c)
target_include_directories(MAX31855 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(MAX31855 PUBLIC peripheral_drivers FreeRTOS)
