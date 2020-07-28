cmake_minimum_required(VERSION 3.5)

project(my_muduo_http)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

add_compile_options("--std=c++11")
add_compile_options("-g")


link_directories(../../lib/)
add_executable(httpd ./httpServer.cc)
target_link_libraries(httpd singsing_http singsing_net singsing_base pthread)
