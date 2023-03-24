#include <iostream>
#include <unistd.h>
#include "Server.h"
#include "common/Comms.h"
#include "exceptions/SocketException.h"

const int Server::MAX_CONNECTION_BACKLOG = 10;

Server::Server(const char* address, int port, int maxConnections): Comms(address, port) {
    int responseCode = bind(this->socketFD, (sockaddr*) &this->address, sizeof(this->address));
    if (responseCode == SOCKET_ERROR) {
        throw SocketException("Error occurred while trying to bind socket to port", errno);
    }
    this->connectionReceiver = new ConnectionReceiver(maxConnections);
}

Server::~Server() {
    delete this->connectionReceiver;
    close(this->socketFD);
}

void Server::setOnMessage(MessageFunction onMessageFunction) {
    this->connectionReceiver->setOnMessage(onMessageFunction);
}

void Server::start() {
    int responseCode = listen(this->socketFD, MAX_CONNECTION_BACKLOG);
    if (responseCode == SOCKET_ERROR) {
        throw SocketException("Error occurred while trying to listen on bound socket", errno);
    }

    this->connectionReceiver->start();
    std::cout << "Server started!" << std::endl;

    while (true) {
        // Since the connection receiver runs on a separate thread, we can call the accept
        // method (which blocks) without affecting the reading of incoming messages
        int incomingConnection = accept(this->socketFD, NULL, NULL);
        std::cout << "Connection received!" << std::endl;
        this->connectionReceiver->add(new Connection(incomingConnection));
    }
}
