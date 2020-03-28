#ifndef INFRARRED_COMMAND_H
#define INFRARRED_COMMAND_H

#include <string>
#include <map>

class Command {
public:
    virtual const char* getName() const = 0;
    virtual void execute(const std::map<std::string, std::string>& params) = 0;
};

#endif //INFRARRED_COMMAND_H
