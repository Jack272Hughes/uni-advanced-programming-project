#pragma once
#include "common/Comms.h"
#include "common/Connection.h"
#include "ConnectionReceiver.h"

class Server : public Comms {
private:
    const static int MAX_CONNECTION_BACKLOG;
    ConnectionReceiver* connectionReceiver;
    MessageFunction onMessage;
public:
    Server(const char* address, int port, int maxConnections);
    ~Server();
    void setOnMessage(MessageFunction onMessageFunction);
    void start();
};
