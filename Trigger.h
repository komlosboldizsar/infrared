#ifndef INFRARED_TRIGGER_H
#define INFRARED_TRIGGER_H

#include <string>

class Trigger {
public:
    virtual bool receive(const std::string& code) = 0;
};

#endif //INFRARED_TRIGGER_H
