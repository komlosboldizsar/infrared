#include "ComReceiver.h"
#include "lib-rs232/rs232.h"

ComReceiver::ComReceiver(const char* port) {

    const char* portnr = std::string(port).substr(3).c_str();
    sscanf(portnr, "%d", &portNumber);
    portNumber--;
    int baudrate = 9600, flowcntrl = 0;
    char mode[] = {'8', 'N', '1' , 0};

    if(RS232_OpenComport(portNumber, baudrate, mode, flowcntrl) == 0) {
        printf("Opened port %s\n", port);
    } else {
        printf("Can not open port %s\n", port);
        return;
    }

    portOpened = true;

}

ComReceiver::~ComReceiver() {
    if (!portOpened)
        return;
    RS232_CloseComport(portNumber);
}

void ComReceiver::receiveLoop() {

    if (!portOpened)
        return;

    unsigned char buffer[4096];
    int received = RS232_PollComport(portNumber, buffer, 4096);
    if (received <= 0)
        return;

    receiveBuffer.append((const char*)buffer, received);
    std::size_t found = receiveBuffer.find_first_of("\r\n");
    while (found != std::string::npos) {
        std::string code = receiveBuffer.substr(0, found);
        if (found > 0)
            receivedCodes.push_back(code);
        receiveBuffer.erase(0, found+1);
        found = receiveBuffer.find_first_of("\r\n", found+1);
    }

}
