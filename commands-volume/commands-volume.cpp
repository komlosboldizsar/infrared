#include "../container_includes/container_includes.h"
#include <cstdio>
#include <iostream>
#include <vector>
#include "CommandVolumeAdjust.h"
#include "CommandVolumeMute.h"

class CommandContainerVolume: public CommandContainer {

    Command* CMD_VOLUME_ADJUST = nullptr;
    Command* CMD_VOLUME_MUTE = nullptr;

public:

    virtual int init(void (*registerMethod)(CommandContainer*)) {
        CMD_VOLUME_ADJUST = new CommandVolumeAdjust();
        CMD_VOLUME_MUTE = new CommandVolumeMute();
        registerMethod(this);
        return 0;
    }

    virtual void deinit() {
        if (CMD_VOLUME_ADJUST != nullptr)
            delete CMD_VOLUME_ADJUST;
        if (CMD_VOLUME_MUTE != nullptr)
            delete CMD_VOLUME_MUTE;
    }

    virtual const char* getName() const {
        return "volume";
    }

    virtual const std::vector<Command*> getCommands() const {
        std::vector<Command*> c;
        c.push_back(CMD_VOLUME_ADJUST);
        c.push_back(CMD_VOLUME_MUTE);
        return c;
    }

};

CONTAINER_INIT_TEMPLATE(myContainer,CommandContainerVolume)