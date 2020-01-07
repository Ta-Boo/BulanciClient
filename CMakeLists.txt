cmake_minimum_required(VERSION 3.7)
project(BulanciClient)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(Boost REQUIRED)
SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -pthread")

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIR} ${Boost_INCLUDE_DIRS})

add_executable(BulanciClient main.cpp Comunication/ComunicationManager/ComunicationManager.cpp Comunication/ComunicationManager/ComunicationManager.h Comunication/Message/PlayerFactory.cpp Comunication/Message/PlayerFactory.h Game/Game.cpp Game/Game.h Game/Player.cpp Game/Player.h Game/Bullet.cpp Game/Bullet.h Comunication/Message/Data/PlayerData.cpp Comunication/Message/Data/PlayerData.h)

target_link_libraries(BulanciClient ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${Boost_LIBRARIES} )