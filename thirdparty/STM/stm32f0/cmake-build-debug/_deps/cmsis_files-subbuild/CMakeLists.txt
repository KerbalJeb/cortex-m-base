# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.17.5)

# We name the project and the target for the ExternalProject_Add() call
# to something that will highlight to the user what we are working on if
# something goes wrong and an error message is produced.

project(cmsis_files-populate NONE)

include(ExternalProject)
ExternalProject_Add(cmsis_files-populate
                     "UPDATE_DISCONNECTED" "False" "GIT_REPOSITORY" "https://github.com/STMicroelectronics/cmsis_device_f0.git" "GIT_TAG" "v2.3.5" "GIT_SHALLOW" "ON"
                    SOURCE_DIR          "C:/Users/Ben/Documents/Projects/ArmCortexBase/thirdparty/STM/stm32f0/cmake-build-debug/_deps/cmsis_files-src"
                    BINARY_DIR          "C:/Users/Ben/Documents/Projects/ArmCortexBase/thirdparty/STM/stm32f0/cmake-build-debug/_deps/cmsis_files-build"
                    CONFIGURE_COMMAND   ""
                    BUILD_COMMAND       ""
                    INSTALL_COMMAND     ""
                    TEST_COMMAND        ""
                    USES_TERMINAL_DOWNLOAD  YES
                    USES_TERMINAL_UPDATE    YES
)
