include(FetchContent)
set(NAME CMSIS)
set(CONTENT_NAME ${NAME}_FILES)
string(TOLOWER "${CONTENT_NAME}" lcName)


FetchContent_Declare(${CONTENT_NAME}
    GIT_REPOSITORY https://github.com/STMicroelectronics/cmsis_device_f0.git
    GIT_TAG v2.3.5
    GIT_SHALLOW ON
)

FetchContent_GetProperties(${CONTENT_NAME})

if (NOT ${lcName}_POPULATED)
    message(STATUS "Getting CMSIS headers for STM32F0")
    FetchContent_Populate(${CONTENT_NAME})
endif ()

set(SRC_DIR ${${lcName}_SOURCE_DIR})

add_library(DeviceCMSIS
    ${SRC_DIR}/Source/Templates/system_stm32f0xx.c
    ${SRC_DIR}/Source/Templates/gcc/startup_${MCU_NAME}.s
)

target_include_directories(DeviceCMSIS PUBLIC ${SRC_DIR}/Include)

target_link_libraries(DeviceCMSIS CMSIS_Core)
