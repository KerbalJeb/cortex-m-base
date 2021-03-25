add_library(CMSIS_Mocks
            stm32f0xx.cpp)
target_include_directories(CMSIS_Mocks PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(CMSIS_Mocks
                      PUBLIC
                      DeviceCMSIS)