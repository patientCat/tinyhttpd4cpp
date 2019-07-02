cmake_minimum_required(VERSION 3.5)
project(my_muduo_net)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/../bin)
add_compile_options("-std=c++11")
add_compile_options("-g")


# 一定要先指定库文件目录
#message("${CMAKE_CURRENT_SOURCE_DIR}")
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../lib) 
add_executable(echoServer echoServer.cc)
target_link_libraries(echoServer singsing_net singsing_base pthread)

add_executable(chatServer chatServer.cc)
target_link_libraries(chatServer singsing_net singsing_base pthread)

add_executable(ftpServer ftpServer.cc)
target_link_libraries(ftpServer singsing_net singsing_base pthread)
