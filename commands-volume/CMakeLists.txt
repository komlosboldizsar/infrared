include(${CMAKE_CURRENT_SOURCE_DIR}/container_includes/container.cmake)
command_library(volume volume_target
        commands-volume/commands-volume.cpp
        commands-volume/CommandVolumeAdjust.cpp
        commands-volume/CommandVolumeMute.cpp)