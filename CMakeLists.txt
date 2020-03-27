project(infrarRED CXX)
enable_testing()

SET(CMAKE_CXX_FLAGS "-std=c++11 -fpermissive -Wcomment -Wwrite-strings -Wunknown-pragmas -O3")

cmake_minimum_required(VERSION 2.6)

add_executable(infrared main.cpp)