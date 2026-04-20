cmake_minimum_required(VERSION 4.0.0)

project(lib_sys C)

add_library(lib_sys INTERFACE
    src/cpu.c
    include/lib_sys.c
    src/procfs/procfs.c
    src/sysfs/sysfs.c
)
target_include_directories(lib_sys INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include
)