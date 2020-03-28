#ifndef INFRARED_IPRECEIVER_H
#define INFRARED_IPRECEIVER_H

#include "Receiver.h"

class IpReceiver : public Receiver {
public:
    IpReceiver(unsigned int port);
    ~IpReceiver();
    // Inherited methods
    virtual void receiveLoop();
};

#endif //INFRARED_IPRECEIVER_H
