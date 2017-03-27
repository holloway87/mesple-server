cmake_minimum_required(VERSION 3.6)
project(mesple_server)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp network/Server.cpp network/ServerException.cpp)
add_executable(mesple_server ${SOURCE_FILES})
