set (LIB_NAME FreeRTOS)

set (SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set (CONFIG_DIR ${CMAKE_CURRENT_SOURCE_DIR}/config)
set(PORT_DIR portable/GCC/ARM_CM0)

add_library (${LIB_NAME}
             ${SRC_DIR}/croutine.c
             ${SRC_DIR}/event_groups.c
             ${SRC_DIR}/list.c
             ${SRC_DIR}/queue.c
             ${SRC_DIR}/stream_buffer.c
             ${SRC_DIR}/tasks.c
             ${SRC_DIR}/timers.c
             ${SRC_DIR}/${PORT_DIR}/port.c
             ${CONFIG_DIR}/FreeRTOSApp.c
             )

target_include_directories (${LIB_NAME}
                            PUBLIC ${SRC_DIR}/include
                            PUBLIC ${SRC_DIR}/${PORT_DIR}
                            PUBLIC ${CONFIG_DIR}
                            )