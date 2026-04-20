cmake_minimum_required(VERSION 4.0.0)

project(lib_sys C)

add_library(lib_sys INTERFACE 
    src/cpu.c
    src/procfs/procfs.c
    src/sysfs/sysfs.c
    src/lib_sys.c
)

target_include_directories(lib_sys INTERFACE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    # ${CMAKE_CURRENT_SOURCE_DIR}/src
)
add_executable(test 
    test.c
    src/cpu.c
    src/procfs/procfs.c
    src/sysfs/sysfs.c
    src/lib_sys.c
)
target_include_directories(test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)