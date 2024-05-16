cmake_minimum_required(VERSION 3.29)
project(init C)

add_library(init
    src/banner.c
    src/cmd.c
    src/cmds/banner.c
    src/cmds/clear.c
    src/cmds/exit.c
    src/cmds/getpid.c
    src/cmds/help.c
    src/cmds/reboot.c
    src/cmds/shell.c
    src/cmds/shutdown.c
    src/cmds/sleep.c
    src/init.c
    src/main.c
    src/shell.c
)

set_property(TARGET init PROPERTY C_STANDARD 23)
target_compile_options(init PRIVATE
    -ffreestanding
    -mcmodel=medany
    -Wall
)
target_include_directories(init PRIVATE
    ${LIBC_INCLUDE}
    ${LUA_INCLUDE}
    include
)
