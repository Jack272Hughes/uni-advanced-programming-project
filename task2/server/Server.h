#pragma once
#include "common/Comms.h"
#include "common/Connection.h"
#include "ConnectionReceiver.h"

class Server : public Comms {
private:
    ConnectionReceiver* connectionReceiver;
    MessageFunction onMessage;
    int maxConnections;
public:
    Server(const char* address, int port, int maxConnections);
    ~Server();
    void setOnMessage(MessageFunction onMessageFunction);
    void start();
};
