cmake_minimum_required(VERSION 3.20) # 指定CMake版本

project(CIU32F003 C ASM)    # 设置项目名称、语言

set(CMAKE_C_STANDARD 11)    # 设置 C 语言标准
set(CMAKE_C_STANDARD_REQUIRED ON) # 设置 C 语言标准为必需
set(CMAKE_C_EXTENSIONS ON) # 设置 C 语言扩展为 ON

set(MCU_FLAGS
    -mcpu=cortex-m0plus
    -mthumb
)   # 设置编译器芯片内核、指令集

set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/Linker/ciu32f003x5.ld) # 设置链接脚本路径,也就是 Flash/RAM 的分布

file(GLOB STD_DRIVER_SOURCES CONFIGURE_DEPENDS
    ${CMAKE_SOURCE_DIR}/Drivers/CIU32F003_Lib/Source/*.c
) # 设置标准驱动源文件路径,将 Drivers/CIU32F003_Lib/Source 下的所有 .c 文件添加到 STD_DRIVER_SOURCES 变量中

add_executable(${PROJECT_NAME}.elf
    Core/Src/main.c
    Core/Src/ciu32f003_it.c
    Core/Src/syscalls.c
    Drivers/CMSIS/Device/system_ciu32f003.c
    Startup/gcc/startup_ciu32f003.s
    ${STD_DRIVER_SOURCES}
) # 添加可执行文件及其源文件,列出来的就是要参与编译链接的源文件

target_include_directories(${PROJECT_NAME}.elf PRIVATE
    Core/Inc
    Drivers/CMSIS/Core
    Drivers/CMSIS/Device
    Drivers/CIU32F003_Lib/Include
) # 设置包含目录,指定头文件搜索路径。相当于 Keil 里的 Include Paths

target_compile_options(${PROJECT_NAME}.elf PRIVATE
    ${MCU_FLAGS}
    -ffunction-sections
    -fdata-sections
    -Wall
    -Wextra
    -Wno-unused-parameter
    $<$<CONFIG:Debug>:-Og -g3>
    $<$<CONFIG:Release>:-Os -g0>
)# 指定编译参数。比如 MCU 内核、警告、优化等级、调试信息

target_link_options(${PROJECT_NAME}.elf PRIVATE
    ${MCU_FLAGS}
    -T${LINKER_SCRIPT}
    -Wl,-Map=${PROJECT_NAME}.map
    -Wl,--gc-sections
    -Wl,--print-memory-usage
    --specs=nano.specs
    --specs=nosys.specs
) # 指定链接参数。比如 MCU 内核、链接脚本、生成 map 文件、内存使用情况、链接器选项等

set_property(TARGET ${PROJECT_NAME}.elf APPEND PROPERTY LINK_DEPENDS ${LINKER_SCRIPT}) # 设置链接依赖项,确保链接脚本在构建过程中被正确处理

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${PROJECT_NAME}.elf> ${PROJECT_NAME}.hex
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${PROJECT_NAME}.elf> ${PROJECT_NAME}.bin
    COMMAND ${CMAKE_OBJDUMP} -d -S $<TARGET_FILE:${PROJECT_NAME}.elf> > ${PROJECT_NAME}.lst
    COMMAND ${CMAKE_SIZE} $<TARGET_FILE:${PROJECT_NAME}.elf>
    BYPRODUCTS
        ${PROJECT_NAME}.hex
        ${PROJECT_NAME}.bin
        ${PROJECT_NAME}.lst
    COMMENT "Generating HEX, BIN, LST and size report"
)# 添加自定义命令，在编译完成后生成 HEX、BIN、LST 文件和大小报告。
