add_executable (${PROJECT_NAME}.elf
                main.cpp
                usb_serial.cpp
                )

target_link_libraries (${PROJECT_NAME}.elf PRIVATE FreeRTOS TinyUSB DeviceSystem peripheral_drivers cli)
target_include_directories(${PROJECT_NAME}.elf PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
set (HEX_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.hex)
set (BIN_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.bin)
set (ASM_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.s)

add_custom_command (TARGET ${PROJECT_NAME}.elf POST_BUILD
                    COMMAND ${CMAKE_OBJCOPY} -Oihex $<TARGET_FILE:${PROJECT_NAME}.elf> ${HEX_FILE}
                    COMMAND ${CMAKE_OBJCOPY} -Obinary $<TARGET_FILE:${PROJECT_NAME}.elf> ${BIN_FILE}
                    COMMAND ${CMAKE_OBJDUMP} -d -C -S $<TARGET_FILE:${PROJECT_NAME}.elf> > ${ASM_FILE}
                    COMMENT "Building ${HEX_FILE}
Building ${BIN_FILE}")