cmake_minimum_required(VERSION 3.7)
project(BulanciClient)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIR} )

add_executable(BulanciClient main.cpp Comunication/Socket/Socket.cpp Comunication/Socket/Socket.h Comunication/Message/Message.cpp Comunication/Message/Message.h Comunication/Message/MessageFactory.cpp Comunication/Message/MessageFactory.h Game/Player.cpp Game/Player.h Game/Game.cpp Game/Game.h)

target_link_libraries(BulanciClient ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} )