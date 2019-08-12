cmake_minimum_required(VERSION 3.5)
project(my_muduo_http)

set(LIB_PATH ${CMAKE_SOURCE_DIR}/lib)
set(LIBRARY_OUTPUT_PATH ${LIB_PATH})
add_compile_options("-std=c++11")

set(srcs 
  ./HttpContext.cc
  ./HttpResponse.cc
  ./HttpServer.cc
    )

link_directories(${LIB_PATH})
add_library(singsing_http ${srcs})
target_link_libraries(singsing_http singsing_net singsing_base)

