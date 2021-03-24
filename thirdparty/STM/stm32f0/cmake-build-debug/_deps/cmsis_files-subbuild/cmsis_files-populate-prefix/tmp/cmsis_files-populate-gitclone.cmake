
if(NOT "C:/Users/Ben/Documents/Projects/ArmCortexBase/thirdparty/STM/stm32f0/cmake-build-debug/_deps/cmsis_files-subbuild/cmsis_files-populate-prefix/src/cmsis_files-populate-stamp/cmsis_files-populate-gitinfo.txt" IS_NEWER_THAN "C:/Users/Ben/Documents/Projects/ArmCortexBase/thirdparty/STM/stm32f0/cmake-build-debug/_deps/cmsis_files-subbuild/cmsis_files-populate-prefix/src/cmsis_files-populate-stamp/cmsis_files-populate-gitclone-lastrun.txt")
  message(STATUS "Avoiding repeated git clone, stamp file is up to date: 'C:/Users/Ben/Documents/Projects/ArmCortexBase/thirdparty/STM/stm32f0/cmake-build-debug/_deps/cmsis_files-subbuild/cmsis_files-populate-prefix/src/cmsis_files-populate-stamp/cmsis_files-populate-gitclone-lastrun.txt'")
  return()
endif()

execute_process(
  COMMAND ${CMAKE_COMMAND} -E rm -rf "C:/Users/Ben/Documents/Projects/ArmCortexBase/thirdparty/STM/stm32f0/cmake-build-debug/_deps/cmsis_files-src"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to remove directory: 'C:/Users/Ben/Documents/Projects/ArmCortexBase/thirdparty/STM/stm32f0/cmake-build-debug/_deps/cmsis_files-src'")
endif()

# try the clone 3 times in case there is an odd git clone issue
set(error_code 1)
set(number_of_tries 0)
while(error_code AND number_of_tries LESS 3)
  execute_process(
    COMMAND "C:/Program Files/Git/cmd/git.exe"  clone --no-checkout --depth 1 --no-single-branch "https://github.com/STMicroelectronics/cmsis_device_f0.git" "cmsis_files-src"
    WORKING_DIRECTORY "C:/Users/Ben/Documents/Projects/ArmCortexBase/thirdparty/STM/stm32f0/cmake-build-debug/_deps"
    RESULT_VARIABLE error_code
    )
  math(EXPR number_of_tries "${number_of_tries} + 1")
endwhile()
if(number_of_tries GREATER 1)
  message(STATUS "Had to git clone more than once:
          ${number_of_tries} times.")
endif()
if(error_code)
  message(FATAL_ERROR "Failed to clone repository: 'https://github.com/STMicroelectronics/cmsis_device_f0.git'")
endif()

execute_process(
  COMMAND "C:/Program Files/Git/cmd/git.exe"  checkout v2.3.5 --
  WORKING_DIRECTORY "C:/Users/Ben/Documents/Projects/ArmCortexBase/thirdparty/STM/stm32f0/cmake-build-debug/_deps/cmsis_files-src"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to checkout tag: 'v2.3.5'")
endif()

set(init_submodules TRUE)
if(init_submodules)
  execute_process(
    COMMAND "C:/Program Files/Git/cmd/git.exe"  submodule update --recursive --init 
    WORKING_DIRECTORY "C:/Users/Ben/Documents/Projects/ArmCortexBase/thirdparty/STM/stm32f0/cmake-build-debug/_deps/cmsis_files-src"
    RESULT_VARIABLE error_code
    )
endif()
if(error_code)
  message(FATAL_ERROR "Failed to update submodules in: 'C:/Users/Ben/Documents/Projects/ArmCortexBase/thirdparty/STM/stm32f0/cmake-build-debug/_deps/cmsis_files-src'")
endif()

# Complete success, update the script-last-run stamp file:
#
execute_process(
  COMMAND ${CMAKE_COMMAND} -E copy
    "C:/Users/Ben/Documents/Projects/ArmCortexBase/thirdparty/STM/stm32f0/cmake-build-debug/_deps/cmsis_files-subbuild/cmsis_files-populate-prefix/src/cmsis_files-populate-stamp/cmsis_files-populate-gitinfo.txt"
    "C:/Users/Ben/Documents/Projects/ArmCortexBase/thirdparty/STM/stm32f0/cmake-build-debug/_deps/cmsis_files-subbuild/cmsis_files-populate-prefix/src/cmsis_files-populate-stamp/cmsis_files-populate-gitclone-lastrun.txt"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to copy script-last-run stamp file: 'C:/Users/Ben/Documents/Projects/ArmCortexBase/thirdparty/STM/stm32f0/cmake-build-debug/_deps/cmsis_files-subbuild/cmsis_files-populate-prefix/src/cmsis_files-populate-stamp/cmsis_files-populate-gitclone-lastrun.txt'")
endif()

