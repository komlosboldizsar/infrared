#include "../container_includes/container_includes.h"
#include <cstdio>
#include <iostream>
#include <vector>
#include "CommandPowerSleep.h"

class CommandContainerPower: public CommandContainer {

    Command* CMD_POWER_SLEEP = nullptr;

public:

    virtual int init(void (*registerMethod)(CommandContainer*)) {
        CMD_POWER_SLEEP = new CommandPowerSleep();
        registerMethod(this);
        return 0;
    }

    virtual void deinit() {
        if (CMD_POWER_SLEEP != nullptr)
            delete CMD_POWER_SLEEP;
    }

    virtual const char* getName() const {
        return "power";
    }

    virtual const std::vector<Command*> getCommands() const {
        std::vector<Command*> c;
        c.push_back(CMD_POWER_SLEEP);
        return c;
    }

};

CONTAINER_INIT_TEMPLATE(myContainer,CommandContainerPower)