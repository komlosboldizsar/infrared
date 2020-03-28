#include "Operation.h"
#include "SingleCodeTrigger.h"

Operation::Operation() { }

Operation::~Operation() {
    for (auto& trigger : triggers)
        delete trigger;
    for (auto& action : actions)
        delete action;
}

void Operation::receive(const std::string& code) {
    bool triggered = false;
    for (auto& trigger : triggers)
        if (trigger->receive(code))
            triggered = true;
    if (triggered)
        for (auto& action : actions)
            action->execute();
}

void Operation::addSingleCodeTrigger(const char* code) {
    Trigger* trigger = new SingleCodeTrigger(code);
    triggers.push_back(trigger);
}

void Operation::addAction(const char* commandName, const std::map<std::string, std::string>& params) {
    Action* action = new Action(commandName, params);
    actions.push_back(action);
}
