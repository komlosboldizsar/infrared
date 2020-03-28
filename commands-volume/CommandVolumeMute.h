#ifndef INFRARED_COMMANDVOLUMEMUTE_H
#define INFRARED_COMMANDVOLUMEMUTE_H

#include "../container_includes/container_includes.h"

class CommandVolumeMute : public Command {
private:
    bool getMute();
    void setMute(bool val);
public:
    virtual const char* getName() const;
    virtual void execute(const std::map<std::string, std::string>& params);
};

#endif //INFRARED_COMMANDVOLUMEMUTE_H
