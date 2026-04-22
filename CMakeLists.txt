cmake_minimum_required(VERSION 4.0.0)
project(lib_sys C)

add_library(lib_sys STATIC)

target_include_directories(lib_sys PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_sources(lib_sys PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/cpu.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/procfs/procfs.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/sysfs/sysfs.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/lib_sys.c
)

add_executable(test_lib_sys test.c)

target_link_libraries(test_lib_sys PRIVATE lib_sys)
