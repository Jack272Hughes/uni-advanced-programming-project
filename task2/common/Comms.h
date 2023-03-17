#pragma once
#include <netinet/in.h>

class Comms {
protected:
    int socketFD;
    sockaddr_in address;
public:
    const static int SOCKET_ERROR = -1;
    const static int SOCKER_CLOSED = 0;
    Comms(const char* address, int port);
};
