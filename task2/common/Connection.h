#pragma once
#include <string>

class Connection {
private:
    static int MAX_BUFFER_SIZE;
    static struct timeval SELECT_TIMEOUT;
    int socket;
public:
    Connection(int socket);
    ~Connection();
    bool hasPendingMessage();
    void sendMessage(const std::string message);
    std::string receiveMessage();
};
