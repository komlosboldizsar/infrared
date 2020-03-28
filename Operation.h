#ifndef INFRARED_OPERATION_H
#define INFRARED_OPERATION_H

#include <vector>
#include "Trigger.h"
#include "Action.h"

class Operation {
private:
    std::vector<Trigger*> triggers;
    std::vector<Action*> actions;
public:
    Operation();
    ~Operation();
    void receive(const std::string& code);
    // Add triggers
    void addSingleCodeTrigger(const char* code);
    // Add actions
    void addAction(const char* commandName, const std::map<std::string, std::string>& params);
};

#endif //INFRARED_OPERATION_H
