#ifndef INFRARED_COMMANDPOWERSLEEP_H
#define INFRARED_COMMANDPOWERSLEEP_H

#include "../container_includes/container_includes.h"

class CommandPowerSleep : public Command {
public:
    virtual const char* getName() const;
    virtual void execute(const std::map<std::string, std::string>& params);
};

#endif //INFRARED_COMMANDPOWERSLEEP_H
