cmake_minimum_required(VERSION 3.5)
project(my_muduo_net)

set(LIB_PATH ${CMAKE_SOURCE_DIR}/lib/)
set(LIBRARY_OUTPUT_PATH ${LIB_PATH})
add_compile_options("-std=c++11")

set(srcs 
    Acceptor.cc
    TcpConnection.cc
    InetAddress.cc
    TimerQueue.cc
    EpollPoller.cc
    ReactorThreadPool.cc
    ReactorThread.cc
    ThreadPool.cc
    Buffer.cc
    Reactor.cc
    TcpServer.cc
    Handler.cc
    Socket.cc
    )

link_directories(${LIB_PATH})
add_library(singsing_net ${srcs})
target_link_libraries(singsing_net singsing_base)

