#pragma once
#include <thread>
#include <set>
#include "common/Connection.h"

typedef void (*MessageFunction)(Connection* connection, std::string message);

class ConnectionReceiver {
private:
    std::set<Connection*> connections;
    int maxConnections;
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
