cmake_minimum_required(VERSION 3.5)
project(my_muduo)

message (STATUS ${CMAKE_BINARY_DIR})
message (STATUS ${CMAKE_SOURCE_DIR})

set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib/)
add_compile_options("-std=c++11")

set(srcs 
    CountDownLatch.cc
    CurrentThread.cc
    Logging.cc
    LogStream.cc
    Timestamp.cc
    )

add_library(singsing_base ${srcs})

