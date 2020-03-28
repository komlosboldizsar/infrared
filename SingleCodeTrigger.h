#ifndef INFRARED_SINGLECODETRIGGER_H
#define INFRARED_SINGLECODETRIGGER_H

#include "Trigger.h"

class SingleCodeTrigger : public Trigger {
private:
    const std::string code;
public:
    SingleCodeTrigger(const char* code);
    virtual bool receive(const std::string& code);
};

#endif //INFRARED_SINGLECODETRIGGER_H