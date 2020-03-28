#ifndef INFRARED_COMMANDVOLUMEADJUST_H
#define INFRARED_COMMANDVOLUMEADJUST_H

#include "../container_includes/container_includes.h"

class CommandVolumeAdjust : public Command {
private:
    double getVolume();
    void setVolume(double val);
public:
    virtual const char* getName() const;
    virtual void execute(const std::map<std::string, std::string>& params);
};

#endif //INFRARED_COMMANDVOLUMEADJUST_H
