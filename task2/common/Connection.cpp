#include <sys/socket.h>
#include <unistd.h>
#include <iostream>
#include <vector>
#include "exceptions/SocketException.h"
#include "Connection.h"
#include "Comms.h"

int Connection::MAX_BUFFER_SIZE = 128;
struct timeval Connection::SELECT_TIMEOUT = { .tv_sec = 0 };

Connection::Connection(int socket) {
    this->socket = socket;
}

Connection::~Connection() {
    close(this->socket);
}

void Connection::sendMessage(const std::string message) {
    int bytesSent = send(socket, message.c_str(), message.length(), 0);
    if (bytesSent == Comms::SOCKET_ERROR) {
        throw SocketException("Error occurred while trying to send message", errno);
    }
}

bool Connection::hasPendingMessage() {
    fd_set fdsToRead;
    FD_SET(this->socket, &fdsToRead);
    int totalFds = select(this->socket + 1, &fdsToRead, NULL, NULL, &Connection::SELECT_TIMEOUT);

    if (totalFds == Comms::SOCKET_ERROR) throw new SocketException("Error occured trying to check pending message status", errno);

    return totalFds > 0;
}

std::string Connection::receiveMessage() {
    std::vector<char> buffer(Connection::MAX_BUFFER_SIZE);
    std::string message;
    
    int byteCount = 0;
    do {
        byteCount = recv(socket, &buffer[0], buffer.size(), 0);
        switch(byteCount) {
            case Comms::SOCKET_ERROR:
                throw SocketException("Error occurred while trying to receive message", errno);
            case Comms::SOCKER_CLOSED:
                throw SocketException("The connection was closed by the client");
            default:
                message.append(buffer.cbegin(), buffer.cend());
        }
    } while (byteCount == Connection::MAX_BUFFER_SIZE && hasPendingMessage());

    return message;
}
