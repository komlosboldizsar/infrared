#include "CommandPowerSleep.h"
#include <stdio.h>
#include <windows.h>
#include <powrprof.h>
#include <iostream>

const char* CommandPowerSleep::getName() const {
    return "power.sleep";
}

void CommandPowerSleep::execute(const std::map<std::string, std::string>& params) {
    SetSuspendState(false, true, false);
};