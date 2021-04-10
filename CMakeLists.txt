cmake_minimum_required(VERSION 3.17)


project(ArmCortexBase)
enable_language(C CXX ASM)


set(CMAKE_CXX_STANDARD 20)
set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/LinkerScript.ld)


if (CMAKE_CROSSCOMPILING)
add_compile_options(
        -mfloat-abi=${MFLOAT}
        -mcpu=${MCPU} -mthumb -mthumb-interwork
        -fno-exceptions
)

add_link_options(
        -Wl,-gc-sections,--print-memory-usage,-Map=${PROJECT_BINARY_DIR}/${PROJECT_NAME}.map
        -mcpu=${MCPU} -mthumb -mthumb-interwork
        --specs=nano.specs
        -T ${LINKER_SCRIPT}
)
endif ()

add_compile_options(
        -ffunction-sections -fdata-sections -fno-common -fmessage-length=0
        -Wall -Wno-unused-variable -Wno-unused-function
        -Og
)


set(MCU_NAME stm32f042x6)
add_definitions(-DSTM32F0)
add_definitions(-DSTM32F042x6)

if(CMAKE_CROSSCOMPILING)
  add_subdirectory(app)
endif()
add_subdirectory(thirdparty)
add_subdirectory(lib)
