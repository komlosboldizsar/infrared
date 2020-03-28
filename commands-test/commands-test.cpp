#include "../container_includes/container_includes.h"
#include <cstdio>
#include <iostream>
#include <vector>

class CommandPrintHello : public Command {
public:
    virtual const char* getName() const {
        return "hello";
    }
    virtual void execute(const std::map<std::string, std::string>& params){
        printf("HELLO from test command\n");
    };
};

class CommandContainerTest : public CommandContainer {

    Command* CMD_PRINT_HELLO = nullptr;

public:

    virtual int init(void (*registerMethod)(CommandContainer*)) {
        CMD_PRINT_HELLO = new CommandPrintHello();
        registerMethod(this);
        return 0;
    }

    virtual void deinit() {
        if (CMD_PRINT_HELLO != nullptr)
            delete CMD_PRINT_HELLO;
    }

    virtual const char* getName() const {
        return "test";
    }

    virtual const std::vector<Command*> getCommands() const {
        std::vector<Command*> c;
        c.push_back(CMD_PRINT_HELLO);
        return c;
    }

};

CONTAINER_INIT_TEMPLATE(myContainer,CommandContainerTest)