#include "CommandRegister.h"

#include <windows.h>
#include <stdio.h>
#include <dirent.h>
#include <string>
#include <iostream>

#include "CommandContainer.h"

typedef int (__cdecl *COMMANDCONT_INIT)(PVOID);

const char* CommandRegister::LIBRARIES_PATH = "./";
const char* CommandRegister::LIBRARIES_EXT = "dll";

CommandRegister::CommandRegister() {
}

void containerRegisterMethod(CommandContainer* container) {
    CommandRegister::getInstance().registerContainer(container);
}

void CommandRegister::initContainers(){

    struct dirent* entry = nullptr;
    DIR* directory = nullptr;

    directory = opendir(LIBRARIES_PATH);
    if (directory != nullptr) {
        while ((entry = readdir(directory))) {
            std::string entryName = std::string(entry->d_name);
            std::size_t extPos = entryName.find_last_of(".");
            if (extPos != std::string::npos) {
                std::string ext = entryName.substr(extPos+1);
                if (ext == LIBRARIES_EXT) {
                    std::string entryPath = std::string(LIBRARIES_PATH) + entryName;
                    initContainerFromLibrary(entryPath.c_str());
                }
            }
        }
    }

    closedir(directory);

}

void CommandRegister::initContainerFromLibrary(const char* libName) {

    HINSTANCE lib = LoadLibrary(TEXT(libName));

    if (lib != nullptr) {
        printf("Library loaded: %s\n", libName);
        COMMANDCONT_INIT procInit = (COMMANDCONT_INIT)GetProcAddress(lib, "init");
        if (procInit != nullptr) {
            int initRes = procInit((PVOID)containerRegisterMethod);
            if (initRes == 0) {
                printf("Library initialized: %s\n", libName);
                loadedLibraries.push_back(lib);
            } else {
                printf("Library initalization unsuccessful: %s. Initializer method returned non-zero.\n", libName);
                FreeLibrary(lib);
            }
        } else {
            printf("Library initalization unsuccessful: %s. Couldn't find initializer method.\n", libName);
            FreeLibrary(lib);
        }
    }

}

void CommandRegister::deinitContainers() {
    for(auto const& container : registeredContainers)
        container->deinit();
    registeredCommands.clear();
    registeredContainers.clear();
    for(auto const& library : loadedLibraries)
        FreeLibrary(library);
    loadedLibraries.clear();
}

void CommandRegister::registerContainer(CommandContainer* container) {

    registeredContainers.push_back(container);
    const char* containerName = container->getName();
    printf("Registered container [%s]\n", containerName);

    for(auto const& command : container->getCommands()) {
        const char* commandName = command->getName();
        registeredCommands.emplace(std::string(commandName), command);
        printf("Registered command [%s] from container [%s]\n", commandName, containerName);
    }

}

const Command* CommandRegister::getCommandByName(const std::string &name) {
    if (registeredCommands.count(name))
        return registeredCommands[name];
    return nullptr;
}