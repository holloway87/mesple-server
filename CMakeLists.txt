cmake_minimum_required(VERSION 3.6)
project(mesple_server)

set(CMAKE_CXX_STANDARD 14)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set(SOURCE_FILES main.cpp network/Server.cpp network/ServerException.cpp network/ConnectionManager.cpp
        entity/Client.cpp network/command/BaseCommand.cpp)
add_executable(mesple_server ${SOURCE_FILES})
target_link_libraries(mesple_server Threads::Threads)
