cmake_minimum_required(VERSION 4.0.0)

add_executable(test test.c)

target_link_libraries(test PRIVATE lib_sys)

target_include_directories(test PRIVATE ${CMAKE_SOURCE_DIR}/include)