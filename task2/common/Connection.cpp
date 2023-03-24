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

// The destructor makes sure to close the socket otherwise the program
// will fail if there are too many file descriptors associated with it
Connection::~Connection() {
    close(this->socket);
}

void Connection::sendMessage(const std::string message) {
    int bytesSent = send(socket, message.c_str(), message.length(), 0);
    if (bytesSent == Comms::SOCKET_ERROR) {
        throw SocketException("Error occurred while trying to send message", errno);
    }
}

// For some methods you would instead have the user pass a char buffer by reference as an argument
// along with the size, but I've taken an alternative approach of instead returning a C++ string
// type so that the user does not need to worry about the length of the incoming message
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
        // Once a message is received there is no way to determine how much data is sent.
        // To counter this it checks to see if it filled up its buffer on the last read
        // and if it has there is a possibility there is still something else to read.

        // It checks if there is a pending message before doing another read, since
        // the message length could coincidentally just equal the max buffer size and it will
        // get stuck waiting for more data when there is nothing else to read.
    } while (byteCount == Connection::MAX_BUFFER_SIZE && hasPendingMessage());

    return message;
}

bool Connection::hasPendingMessage() {
    fd_set fdsToRead;
    FD_SET(this->socket, &fdsToRead);
    // This will check all the sockets defined in "fdsToRead" and return the total
    // count of sockets with pending requests. In this case that is a maximum of 1
    int totalFds = select(this->socket + 1, &fdsToRead, NULL, NULL, &Connection::SELECT_TIMEOUT);

    if (totalFds == Comms::SOCKET_ERROR) throw SocketException("Error occured trying to check pending message status", errno);

    return totalFds > 0;
}
