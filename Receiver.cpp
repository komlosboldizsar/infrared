#include "Receiver.h"

bool Receiver::hasReceived() {
    return !receivedCodes.empty();
}

std::string Receiver::nextReceived() {
    if (receivedCodes.empty())
        return std::string("");
    std::string returnValue = receivedCodes[0];
    receivedCodes.erase(receivedCodes.begin());
    return returnValue;
}
