set (NAME CMSIS)

set (PORT_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/cmsis_device_f0)
set (MOCK_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/cmsis_device_f0_mock)
get_target_property (CMSIS_CORE_INC CMSIS_Core INTERFACE_INCLUDE_DIRECTORIES)

if (CMAKE_CROSSCOMPILING)
  add_library (DeviceSystem
               ${PORT_SRC_DIR}/Source/Templates/system_stm32f0xx.c
               ${PORT_SRC_DIR}/Source/Templates/gcc/startup_${MCU_NAME}.s
               )
  target_include_directories (DeviceSystem PUBLIC ${PORT_SRC_DIR}/Include)

  add_library (DeviceCMSIS INTERFACE)
  target_include_directories (DeviceCMSIS INTERFACE ${PORT_SRC_DIR}/Include ${CMSIS_CORE_INC})

  target_link_libraries (DeviceSystem CMSIS_Core)
else()
  add_library(DeviceCMSIS ${MOCK_SRC_DIR}/stm32f0xx.cpp)
  target_include_directories(DeviceCMSIS
                             PUBLIC ${MOCK_SRC_DIR}
                             PUBLIC ${PORT_SRC_DIR}/Include
                             PUBLIC ${CMSIS_CORE_INC}
                             )
endif ()


