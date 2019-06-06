cmake_minimum_required(VERSION 3.5)
project(my_muduo_net)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/../bin)
add_compile_options("-std=c++11")

set(srcs 
    main.cc
    General.cc
    ThreadPool.cc
    CountDownLatch.cc
    Httpd.cc
    TcpConnection.cc
    Socket.cc
    )

# 一定要先指定库文件目录
link_directories(/home/jmx/project/tinyhttpd4cpp/httpd_ver3/lib/) 
add_executable(httpd ${srcs})

target_link_libraries(httpd logger4cpp)
target_link_libraries(httpd pthread)
