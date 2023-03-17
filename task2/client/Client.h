#pragma once

#include <string>
#include "common/Comms.h"
#include "common/Connection.h"

class Client : public Comms {
private:
    Connection* connection;
public:
    Client(const char* address, int port);
    ~Client();
    void send(std::string message);
    std::string receive();
};
