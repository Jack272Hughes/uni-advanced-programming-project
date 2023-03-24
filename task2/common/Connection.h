#pragma once
#include <string>
#include <mutex>

class Connection {
private:
    // Static constant to set how many bytes
    // to read from the socket at once
    static int MAX_BUFFER_SIZE;
    // Static constant for how long the "select" function
    // should wait before returning its count
    static struct timeval SELECT_TIMEOUT;
    int socket;
public:
    Connection(int socket);
    ~Connection();
    void sendMessage(const std::string message);
    std::string receiveMessage();
    bool hasPendingMessage();
};
