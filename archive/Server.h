#pragma once
#include "common/Comms.h"
#include "common/Connection.h"
#include "ConnectionReceiver.h"

#pragma once
#include "common/Comms.h"
#include "common/Connection.h"

class Server : public Comms {
public:
    Server(const char* address, int port);
    ~Server();
    void start(int maxConnections);
};
