project(infraRED CXX)
enable_testing()

SET(CMAKE_CXX_FLAGS "-std=c++11 -fpermissive -Wcomment -Wwrite-strings -Wunknown-pragmas -O3")

cmake_minimum_required(VERSION 2.6)

add_executable(infrared main.cpp
        CommandRegister.cpp
        Action.cpp
        Trigger.cpp
        SingleCodeTrigger.cpp
        Operation.cpp
        Receiver.cpp
        ComReceiver.cpp
        IpReceiver.cpp
        lib-tinyxml2/tinyxml2.cpp
        lib-rs232/rs232.cpp)

function(add_command_library lib_directory)
    include(${CMAKE_CURRENT_SOURCE_DIR}/commands-${lib_directory}/CMakeLists.txt)
endfunction()

add_command_library(test)
add_command_library(volume)
add_command_library(power)
