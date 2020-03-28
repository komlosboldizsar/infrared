include(${CMAKE_CURRENT_SOURCE_DIR}/container_includes/container.cmake)
command_library(power power_target
        commands-power/commands-power.cpp
        commands-power/CommandPowerSleep.cpp)
target_link_libraries(${power_target} powrprof)