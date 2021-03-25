set (NAME CMSIS)

set (PORT_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/cmsis_device_f0)

add_library (DeviceSystem
             ${PORT_SRC_DIR}/Source/Templates/system_stm32f0xx.c
             ${PORT_SRC_DIR}/Source/Templates/gcc/startup_${MCU_NAME}.s
             )

target_include_directories (DeviceSystem PUBLIC ${PORT_SRC_DIR}/Include)
get_target_property (CMSIS_CORE_INC CMSIS_Core INTERFACE_INCLUDE_DIRECTORIES)

add_library (DeviceCMSIS INTERFACE)
target_include_directories (DeviceCMSIS INTERFACE ${PORT_SRC_DIR}/Include ${CMSIS_CORE_INC})

target_link_libraries (DeviceSystem CMSIS_Core)
