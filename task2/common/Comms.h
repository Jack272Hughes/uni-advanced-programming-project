#pragma once
#include <netinet/in.h>

class Comms {
protected:
    // These are protected since only the subclasses
    // will need to interact with them
    int socketFD;
    sockaddr_in address;
public:
    // Static constants for when a socket function returns a response code
    // so that there are no unexplained, "floating" -1's or 0's everywhere
    const static int SOCKET_ERROR = -1;
    const static int SOCKER_CLOSED = 0;
    Comms(const char* address, int port);
};
