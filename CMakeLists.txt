cmake_minimum_required(VERSION 3.29)
project(init C)

add_library(init
    src/cmd.c
    src/cmds/clear.c
    src/cmds/echo.c
    src/cmds/exit.c
    src/cmds/getpid.c
    src/cmds/help.c
    src/cmds/motd.c
    src/cmds/reboot.c
    src/cmds/shutdown.c
    src/cmds/sleep.c
    src/init.c
    src/shell.c
    src/tok.c
)

set_property(TARGET init PROPERTY C_STANDARD 23)
set_property(TARGET init PROPERTY COMPILE_WARNING_AS_ERROR ON)
target_compile_options(init PRIVATE -ffreestanding -mcmodel=medany -Wall)
target_include_directories(init PRIVATE ${LIBC_INCLUDE} include)
