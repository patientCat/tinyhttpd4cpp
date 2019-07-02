cmake_minimum_required(VERSION 3.5)
project(my_muduo_net)

set(LIBRARY_OUTPUT_PATH /home/jmx/project/tinyhttpd4cpp/httpd_ver4/lib)
add_compile_options("-std=c++11")

set(srcs 
    CountDownLatch.cc
    CurrentThread.cc
    General.cc
    Logging.cc
    LogStream.cc
    Timestamp.cc
    )

add_library(singsing_base ${srcs})

