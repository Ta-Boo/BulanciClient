cmake_minimum_required(VERSION 3.13)
project(BulanciClient)

set(CMAKE_CXX_STANDARD 14)

add_executable(BulanciClient main.cpp Comunication/Socket/Socket.cpp Comunication/Socket/Socket.h)