cmake_minimum_required(VERSION 3.5)
project(my_muduo_lib)

message(STATUS ${CMAKE_BINARY_DIR})
message(STATUS ${CMAKE_SOURCE_DIR})

add_subdirectory(net)
add_subdirectory(base)
add_subdirectory(http)
