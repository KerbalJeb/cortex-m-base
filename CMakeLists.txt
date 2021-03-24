cmake_minimum_required(VERSION 3.17)


project(ArmCortexBase C CXX ASM)


set(CMAKE_CXX_STANDARD 14)
set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/LinkerScript.ld)

add_compile_options(
        -mfloat-abi=${MFLOAT}
        -mcpu=${MCPU} -mthumb -mthumb-interwork
        -ffunction-sections -fdata-sections -fno-common -fmessage-length=0 -fno-exceptions
        -Wall -Wno-unused-variable -Wno-unused-function
        -Og
)

add_link_options(
        -Wl,-gc-sections,--print-memory-usage,-Map=${PROJECT_BINARY_DIR}/${PROJECT_NAME}.map
        -mcpu=${MCPU} -mthumb -mthumb-interwork
        --specs=nano.specs
        -T ${LINKER_SCRIPT}
)

set(MCU_NAME stm32f042x6)
add_definitions(-DSTM32F0)
add_definitions(-DSTM32F042x6)


add_subdirectory(thirdparty)
add_subdirectory(src)



