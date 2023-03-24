#pragma once
#include <thread>
#include "common/Connection.h"

typedef void (*MessageFunction)(Connection* connection, std::string message);

class ConnectionReceiver {
private:
    Connection** connections;
    int totalConnections;
    MessageFunction onMessage;
    std::thread handlerThread;
    void handleConnections();
public:
    ConnectionReceiver(int maxConnections);
    ~ConnectionReceiver();
    void add(Connection* connection);
    void start();
    void setOnMessage(MessageFunction function);
};
