#ifndef INFRARRED_COMMANDCONTAINER_H
#define INFRARRED_COMMANDCONTAINER_H

#include <vector>
#include "Command.h"

class CommandContainer {
public:
    virtual int init(void (*registerMethod)(CommandContainer*)) = 0;
    virtual void deinit() = 0;
    virtual const char* getName() const = 0;
    virtual const std::vector<Command*> getCommands() const = 0;
};

#define CONTAINER_INIT_TEMPLATE(VAR,CLASS)  CLASS* VAR = nullptr; \
                                            extern "C" __declspec(dllexport) int init(void (*registerMethod)(CommandContainer*)) { \
                                                if (VAR == nullptr) { \
                                                    VAR = new CLASS(); \
                                                    return VAR->init(registerMethod); \
                                                } \
                                                return 1; \
                                            }

#endif //INFRARRED_COMMANDCONTAINER_H
