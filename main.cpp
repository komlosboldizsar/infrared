//
// Created by Boldi on 2020. 03. 27..
//

#include <cstdio>
#include <iostream>
#include "CommandRegister.h"
#include "lib-tinyxml2/tinyxml2.h"

int main(int argc, char** argv) {

    tinyxml2::XMLDocument doc;
    doc.LoadFile("config.xml");
    std::cout << doc.FirstChildElement("infrared")->FirstChild()->GetLineNum() << std::endl;

    CommandRegister::getInstance().initContainers();
    return 0;

}
