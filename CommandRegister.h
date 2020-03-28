#ifndef INFRARRED_COMMAND_REGISTER_H
#define INFRARRED_COMMAND_REGISTER_H

#include <windows.h>
#include <vector>
#include "Command.h"
#include "CommandContainer.h"

class CommandRegister {

    /* SINGLETON THINGS */
public:
    static CommandRegister& getInstance() {
        static CommandRegister instance;
        return instance;
    }
private:
    CommandRegister();
public:
    CommandRegister(CommandRegister const&) = delete;
    void operator=(CommandRegister const&) = delete;

    /* REAL REGISTER THINGS */
private:
    std::vector<HINSTANCE> loadedLibraries;
    std::vector<CommandContainer*> registeredContainers;
    std::map<std::string, Command*> registeredCommands;
public:
    void initContainers();
    void deinitContainers();
    void registerContainer(CommandContainer* container);
    Command* getCommandByName(const std::string& name);
private:
    static const char* LIBRARIES_PATH;
    static const char* LIBRARIES_EXT;
    void initContainerFromLibrary(const char* libName);
};

#endif //INFRARRED_COMMAND_REGISTER_H
