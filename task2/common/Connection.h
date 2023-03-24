#pragma once
#include <string>
#include <mutex>

class Connection {
private:
    static int MAX_BUFFER_SIZE;
    static struct timeval SELECT_TIMEOUT;
    int socket;
public:
    Connection(int socket);
    ~Connection();
    void sendMessage(const std::string message);
    std::string receiveMessage();
    bool hasPendingMessage();
};
