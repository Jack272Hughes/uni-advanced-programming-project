#include "Client.h"
#include "common/Comms.h"
#include "exceptions/SocketException.h"

Client::Client(const char* address, int port): Comms(address, port) {
    int responseCode = connect(this->socketFD, (sockaddr*) &this->address, sizeof(this->address));

    if (responseCode == SOCKET_ERROR) {
        throw SocketException("Error occurred while trying to connect", errno);
    }

    connection = new Connection(this->socketFD);
}

Client::~Client() {
    delete this->connection;
}

void Client::send(std::string message) {
    connection->sendMessage(message);
}

std::string Client::receive() {
    return connection->receiveMessage();
}
