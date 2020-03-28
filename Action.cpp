#include "Action.h"
#include "CommandRegister.h"

Action::Action(const char* commandName, const std::map<std::string, std::string>& params):
    params(params)
{
    this->command = CommandRegister::getInstance().getCommandByName(std::string(commandName));
}

void Action::execute() {
    command->execute(params);
}
