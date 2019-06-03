cmake_minimum_required(VERSION 3.5)
project(my_muduo_net)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/../bin)
add_compile_options("-std=c++11")

set(net_SRCS 
    Httpd.cc
    Socket.cc
    TcpConnection.cc
    General.cc
    main.cc)

add_executable(main ${net_SRCS})
target_link_libraries(main pthread)
