#ifndef INFRARED_RECEIVER_H
#define INFRARED_RECEIVER_H

#include <string>
#include <vector>

class Receiver {
protected:
    std::vector<std::string> receivedCodes;
public:
    virtual void receiveLoop() = 0;
    virtual bool hasReceived();
    virtual std::string nextReceived();
};

#endif //INFRARED_RECEIVER_H
