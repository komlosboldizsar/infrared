//
// Created by Boldi on 2020. 03. 27..
//

#include <cstdio>
#include <iostream>

#include "lib-tinyxml2/tinyxml2.h"

#include "CommandRegister.h"
#include "Operation.h"
#include "Receiver.h"
#include "ComReceiver.h"
#include "IpReceiver.h"

std::vector<Receiver*> receivers;
std::vector<Operation*> operations;

int readConfig();

int main(int argc, char** argv) {
    CommandRegister::getInstance().initContainers();
    readConfig();
    return 0;
}

int readConfig() {

    tinyxml2::XMLDocument doc;
    doc.LoadFile("config.xml");
    tinyxml2::XMLNode* rootElement = doc.FirstChildElement("infrared");
    if (rootElement == nullptr) {
        // TODO: error message
        return 1;
    }

    tinyxml2::XMLNode* receiversRoot = rootElement->FirstChildElement("receivers");
    if (receiversRoot != nullptr) {
        tinyxml2::XMLNode* receiver = receiversRoot->FirstChild();
        while (receiver != nullptr) {

            const char* receiverType = receiver->Value();

            tinyxml2::XMLElement* receiverElement = receiver->ToElement();
            if (receiverElement == nullptr)
                continue; // TODO: error message

            if (strcmp(receiverType, "ip") == 0) {
                const tinyxml2::XMLAttribute* portAttribute = receiverElement->FindAttribute("port");
                if (portAttribute == nullptr)
                    continue; // TODO: error message
                unsigned int port;
                sscanf(portAttribute->Value(), "%u", &port);
                Receiver* receiverObj = new IpReceiver(port);
                // TODO: address prefixes
                receivers.push_back(receiverObj);
            }

            if (strcmp(receiverType, "com") == 0) {
                const tinyxml2::XMLAttribute* portAttribute = receiverElement->FindAttribute("port");
                if (portAttribute == nullptr)
                    continue; // TODO: error message
                const char* port = portAttribute->Value();
                Receiver* receiverObj = new ComReceiver(port);
                receivers.push_back(receiverObj);
            }

            receiver = receiver->NextSibling();

        }
    }

    tinyxml2::XMLNode* operationsRoot = rootElement->FirstChildElement("operations");
    if (operationsRoot != nullptr) {

        tinyxml2::XMLNode* operation = operationsRoot->FirstChild();
        while (operation != nullptr) {

            Operation* operationObj = new Operation();

            if (strcmp(operation->Value(), "operation") != 0)
                continue; // TODO: error message

            tinyxml2::XMLNode* triggersRoot = rootElement->FirstChildElement("triggers");
            if (triggersRoot != nullptr) {
                tinyxml2::XMLNode* triggerNode = triggersRoot->FirstChild();
                while(triggerNode != nullptr) {

                    if (strcmp(triggerNode->Value(), "single-code") == 0) {
                        tinyxml2::XMLElement* triggerElement = triggerNode->ToElement();
                        if (triggerElement == nullptr)
                            continue; // TODO: error message
                        const tinyxml2::XMLAttribute* valueAttribute = triggerElement->FindAttribute("value");
                        if (valueAttribute == nullptr)
                            continue; // TODO: error message
                        const char* code = valueAttribute->Value();
                        operationObj->addSingleCodeTrigger(code);
                    }

                    triggerNode = triggerNode->NextSibling();

                }
            }

            tinyxml2::XMLNode* action = rootElement->FirstChildElement("action");
            while (action != nullptr) {

                tinyxml2::XMLElement* actionElement = action->ToElement();
                if (actionElement == nullptr)
                    continue; // TODO: error message
                const tinyxml2::XMLAttribute* commandAttribute = actionElement->FindAttribute("command");
                if (commandAttribute == nullptr)
                    continue; // TODO: error message
                const char* commandName = commandAttribute->Value();

                std::map<std::string, std::string> params;
                tinyxml2::XMLNode* param = action->FirstChildElement("param");
                while(param != nullptr) {

                    param = action->NextSiblingElement("param");

                    tinyxml2::XMLElement* paramElement = action->ToElement();
                    if (paramElement == nullptr)
                        continue; // TODO: error message

                    const tinyxml2::XMLAttribute* nameAttribute = actionElement->FindAttribute("name");
                    const tinyxml2::XMLAttribute* valueAttribute = actionElement->FindAttribute("value");
                    if ((nameAttribute == nullptr) || (valueAttribute == nullptr))
                        continue; // TODO: error message
                    params.emplace(nameAttribute->Value(), valueAttribute->Value());

                }

                operationObj->addAction(commandName, params);

                action = action->NextSiblingElement("action");

            }

            operation = operation->NextSibling();

        }

    }

}
