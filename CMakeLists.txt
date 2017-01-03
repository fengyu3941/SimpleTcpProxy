cmake_minimum_required(VERSION 2.6)

project(tcpproxy)

find_package(Boost REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

add_executable(tcpproxy tcpproxy_main.cpp tcpproxy_server.hpp tcpproxy_server.cpp tcpproxy_connection.hpp tcpproxy_connection.cpp)

