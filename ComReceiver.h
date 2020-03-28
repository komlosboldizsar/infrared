#ifndef INFRARED_COMRECEIVER_H
#define INFRARED_COMRECEIVER_H

#include "Receiver.h"

class ComReceiver : public Receiver {
public:
    ComReceiver(const char* port);
    ~ComReceiver();
    // Inherited methods
    virtual void receiveLoop();
};

#endif //INFRARED_COMRECEIVER_H
