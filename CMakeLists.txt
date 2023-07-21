# Template CMakeLists.txt configuration for STM32 MCUS
cmake_minimum_required(VERSION 3.22.1)
# ##############################################################################
# Edit your MCU information up to the next border
project(f429i-disc-project)
set(PROJECT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

## Needs to specify the MCU target(MCU_TARGET) and board(BOARD)

## MCU information
if (NOT MCU_TARGET) # error message. The MCU_TARGET is not specified
    message(FATAL_ERROR "MCU_TARGET is not specified")
elseif(MCU_TARGET MATCHES "^STM32F429")
    set(MCU_FAMILY STM32F4xx)
    set(MCU_MODEL STM32F429xx)
    # set(MCU_MODEL STM32F42_43xxx)
    set(CPU_PARAMETERS
        -mcpu=cortex-m4
        -mthumb
        -mfpu=fpv4-sp-d16
        -mfloat-abi=hard)
    set(STARTUP_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/src/main/startup/startup_stm32f429x.s)   
    set(MCU_LINKER_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/src/link/STM32F429ZITX_FLASH.ld)

    # FreeRTOS
    set(CMSIS_DEVICE_HEADER stm32f4xx.h)

    # Libraries
    # Headers
    set(TARGET_LIB_INCLUDE_DIRECTORIES
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/STM32F4/STM32F4xx_HAL_Driver/Inc
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/STM32F4/STM32F4xx/Include
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/STM32F4/Core
    )

    # Sources
    file(GLOB_RECURSE LIB_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/STM32F4/*.c
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/Middlewares/*.c
    )

elseif(MCU_TARGET MATCHES "^STM32H723")
    set(MCU_FAMILY STM32H7xx)
    set(MCU_MODEL STM32H723xx)
    set(CPU_PARAMETERS
        -mcpu=cortex-m7
        -mthumb
        -mfpu=fpv5-sp-d16
        -mfloat-abi=hard)


    if(MCU_TARGET MATCHES "STM32H723VET6")
        set(STARTUP_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/src/main/startup/startup_stm32h723vetx.s)
        set(MCU_LINKER_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/src/link/STM32H723VETX_FLASH.ld)        
    elseif(MCU_TARGET MATCHES "STM32H723VGT6")
        set(STARTUP_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/src/main/startup/startup_stm32h723vgtx.s)
        set(MCU_LINKER_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/src/link/STM32H723VGTX_FLASH.ld)
    endif()

    # FreeRTOS
    set(CMSIS_DEVICE_HEADER stm32h7xx.h)

    # Libraries
    # Headers
    set(TARGET_LIB_INCLUDE_DIRECTORIES
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/STM32H7/STM32H7xx_HAL_Driver/Inc
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/STM32H7/STM32H7xx/Include
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/STM32H7/Core
    )

    # Sources
    file(GLOB_RECURSE LIB_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/STM32H7/*.c
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/Middlewares/*.c
    )

endif()

# Headers
set(LIB_INCLUDE_DIRECTORIES
${TARGET_LIB_INCLUDE_DIRECTORIES}
${CMAKE_CURRENT_SOURCE_DIR}/lib/CMSIS/Include
${CMAKE_CURRENT_SOURCE_DIR}/lib/Middlewares/FreeRTOS/Source/include
${CMAKE_CURRENT_SOURCE_DIR}/lib/Middlewares/FreeRTOS/Source/portable/GCC/ARM_CM4F
${CMAKE_CURRENT_SOURCE_DIR}/lib/Middlewares/FreeRTOS/Source/CMSIS_RTOS_V2
${CMAKE_CURRENT_SOURCE_DIR}/lib/utilites/etl/etl/include ) # ETL library

# ##############################################################################
set(EXECUTABLE ${CMAKE_PROJECT_NAME})
enable_language(C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

set(PROJECT_INCLUDE_DIRECTORIES
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${PROJECT_DIR}/main
    ${PROJECT_DIR}/main/core
    ${PROJECT_DIR}/rtos
    )       # Thats just for now


# Project sources
file(GLOB_RECURSE PROJECT_SOURCES FOLLOW_SYMLINKS
    ${PROJECT_DIR}/*.cpp
    ${PROJECT_DIR}/*.c )

# ETL
set(GIT_DIR_LOOKUP_POLICY ALLOW_LOOKING_ABOVE_CMAKE_SOURCE_DIR)
add_subdirectory(lib/utilities/etl/etl)

# Executable files
add_executable(${EXECUTABLE}
    ${LIB_SOURCES} 
    ${PROJECT_SOURCES}
    ${STARTUP_SCRIPT})

# ETL
target_link_libraries(${EXECUTABLE} PRIVATE etl::etl)

# Embedded macros(defines)
 target_compile_definitions(${EXECUTABLE} PRIVATE
    ${MCU_MODEL}
    ${MCU_FAMILY}
    #USE_STDPERIPH_DRIVER
    USE_DEFAULT_TIMEOUT_CALLBACK
    USE_HAL_DRIVER
    CMSIS_device_header="${CMSIS_DEVICE_HEADER}")

# Add header directories (AFTER add_executable !!)
target_include_directories(${EXECUTABLE} PRIVATE
    ${LIB_INCLUDE_DIRECTORIES}
    ${PROJECT_INCLUDE_DIRECTORIES})

# Compiler and linker options
target_compile_options(${EXECUTABLE} PRIVATE
    ${CPU_PARAMETERS}
    -Wall
    -Wextra
    -Wpedantic
    -Wno-unused-parameter
    #-fopt-info-optimized
    $<$<COMPILE_LANGUAGE:CXX>:
        -Wno-volatile
        -Wno-old-style-cast
        -Wuseless-cast
        -Wsuggest-override
        -Werror>
    $<$<CONFIG:Debug>:-Og -g3 -ggdb>
    $<$<CONFIG:Release>:-O3 -g0>)       # Maximum optimization on realease

target_link_options(${EXECUTABLE} PRIVATE
    -T${MCU_LINKER_SCRIPT}
    ${CPU_PARAMETERS}
    -Wl,-Map=${CMAKE_PROJECT_NAME}.map
    --specs=nosys.specs
    -Wl,--start-group
    -lc
    -lm
    -lstdc++
    -Wl,--end-group
    -Wl,--print-memory-usage
    LINKER:--no-warn-rwx-segments)

add_custom_command(TARGET ${EXECUTABLE} POST_BUILD
    COMMAND ${CMAKE_SIZE} $<TARGET_FILE:${EXECUTABLE}>)

add_custom_command(TARGET ${EXECUTABLE} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${EXECUTABLE}>
    ${EXECUTABLE}.hex
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${EXECUTABLE}>
    ${EXECUTABLE}.bin)