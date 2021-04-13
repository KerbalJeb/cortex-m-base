include (FetchContent)
set(FETCHCONTENT_QUIET off)

set(FETCHCONTENT_BASE_DIR ${CMAKE_SOURCE_DIR}/cmake-extern-sources)

add_subdirectory(CMSIS)
add_subdirectory(FakeFunctionFramework)
add_subdirectory(FreeRTOS)
add_subdirectory(ST)
add_subdirectory(TinyUSB)
add_subdirectory(spiffs)

if (NOT CMAKE_CROSSCOMPILING)
  add_subdirectory(googletest)
endif ()
