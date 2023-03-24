#include <iostream>
#include <unistd.h>
#include "Server.h"
#include "common/Comms.h"
#include "exceptions/SocketException.h"

Server::Server(const char* address, int port, int maxConnections): Comms(address, port) {
    int responseCode = bind(this->socketFD, (sockaddr*) &this->address, sizeof(this->address));
    if (responseCode == SOCKET_ERROR) {
        throw SocketException("Error occurred while trying to bind socket to port", errno);
    }
    this->maxConnections = maxConnections;
    this->connectionReceiver = new ConnectionReceiver();
}

Server::~Server() {
    delete this->connectionReceiver;
    close(this->socketFD);
}

void Server::setOnMessage(MessageFunction onMessageFunction) {
    this->connectionReceiver->setOnMessage(onMessageFunction);
}

pthread_mutex_t receivedMessageMutex = PTHREAD_MUTEX_INITIALIZER;
void* handleConnection(void* incoming) {
    Connection* connection = (Connection*) incoming;
    try {
        while (true) {
            std::string message = connection->receiveMessage();

            pthread_mutex_lock(&receivedMessageMutex);
            std::cout << "Message received: " << message << "\nHow would you like to respond?" << std::endl;
            std::string response;
            std::getline(std::cin, response);
            connection->sendMessage(response);
            pthread_mutex_unlock(&receivedMessageMutex);
        }
    } catch(SocketException exception) {
        std::cout << "Received error when handling connection:\n" << exception.what() << std::endl;
    }
    return 0;
}

void Server::start() {
    int responseCode = listen(this->socketFD, maxConnections);
    if (responseCode == SOCKET_ERROR) {
        throw SocketException("Error occurred while trying to listen on bound socket", errno);
    }

    this->connectionReceiver->start();
    std::cout << "Server started!" << std::endl;

    while (true) {
        int incomingConnection = accept(this->socketFD, NULL, NULL);
        std::cout << "Connection received!" << std::endl;
        this->connectionReceiver->add(new Connection(incomingConnection));
    }
}
