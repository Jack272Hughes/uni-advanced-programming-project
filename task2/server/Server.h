#pragma once
#include "common/Comms.h"
#include "common/Connection.h"

typedef void (*MessageFunction)(char* message);

class Server : public Comms {
private:
    MessageFunction onMessage;
public:
    Server(const char* address, int port);
    ~Server();
    void setOnMessage(MessageFunction onMessageFunction);
    void start(int maxConnections);
};
