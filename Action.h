#ifndef INFRARED_ACTION_H
#define INFRARED_ACTION_H

#include "Command.h"
#include <map>

class Action {
private:
    Command* command;
    const std::map<std::string, std::string> params;
public:
    Action(const char* commandName, const std::map<std::string, std::string>& params);
    void execute();
};

#endif //INFRARED_ACTION_H
