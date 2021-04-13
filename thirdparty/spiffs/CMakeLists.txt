add_library(spiffs
            lib/src/spiffs_cache.c
            lib/src/spiffs_check.c
            lib/src/spiffs_gc.c
            lib/src/spiffs_hydrogen.c
            lib/src/spiffs_nucleus.c
            )

target_include_directories(spiffs  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} lib/src)