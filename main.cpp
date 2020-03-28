//
// Created by Boldi on 2020. 03. 27..
//

#include <cstdio>
#include <iostream>
#include "CommandRegister.h"

int main(int argc, char** argv) {
    CommandRegister::getInstance().initContainers();
    return 0;
}
