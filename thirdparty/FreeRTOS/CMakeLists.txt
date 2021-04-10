set (LIB_NAME FreeRTOS)

set (CONFIG_DIR ${CMAKE_CURRENT_SOURCE_DIR}/config)
set (SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/FreeRTOS/Source)
set (PORT_DIR portable/GCC/ARM_CM0)

if (CMAKE_CROSSCOMPILING)


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
else ()
  add_library (${LIB_NAME}
               ${CMAKE_CURRENT_SOURCE_DIR}/mock/Mocktask.c
               ${CMAKE_CURRENT_SOURCE_DIR}/mock/Mockqueue.c
               ${CONFIG_DIR}/FreeRTOSApp.c
               )
  target_include_directories (${LIB_NAME}
                              PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/mock
                              PUBLIC ${SRC_DIR}/include
                              PUBLIC ${SRC_DIR}/${PORT_DIR}
                              PUBLIC ${CONFIG_DIR}
                              )
  target_link_libraries(${LIB_NAME} PUBLIC fff)
endif ()