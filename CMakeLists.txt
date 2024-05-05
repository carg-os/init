cmake_minimum_required(VERSION 3.29)
project(init C)

add_library(init
    src/init.c
    src/main.c
    src/motd.c
)

set_property(TARGET init PROPERTY C_STANDARD 23)
target_compile_options(init PRIVATE -ffreestanding -mcmodel=medany -Wall)
target_include_directories(init PRIVATE ${LIBC_INCLUDE} ${LIBLUA_INCLUDE} include)
