#include <iostream>
#include <unistd.h>
#include "archive/Server.h"
#include "common/Comms.h"
#include "exceptions/SocketException.h"

Server::Server(const char* address, int port): Comms(address, port) {
    int responseCode = bind(this->socketFD, (sockaddr*) &this->address, sizeof(this->address));
    if (responseCode == SOCKET_ERROR) {
        throw SocketException("Error occurred while trying to bind socket to port", errno);
    }
}

Server::~Server() {
    close(this->socketFD);
}

pthread_mutex_t receivedMessageMutex = PTHREAD_MUTEX_INITIALIZER;
void* handleConnection(void* incoming) {
    Connection* connection = (Connection*) incoming;
    try {
        while (true) {
            std::string message = connection->receiveMessage();

            // The mutex is passed in by reference which is then mutated to be locked
            pthread_mutex_lock(&receivedMessageMutex);
            // Originally the server did not allow you to specify the on message function
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

void Server::start(int maxConnections) {
    int responseCode = listen(this->socketFD, maxConnections);
    if (responseCode == SOCKET_ERROR) {
        throw SocketException("Error occurred while trying to listen on bound socket", errno);
    }

    std::cout << "Server started!" << std::endl;
    while (true) {
        int incomingConnection = accept(this->socketFD, NULL, NULL);
        std::cout << "Connection received!" << std::endl;
        // Used pthread instead of the C++ equivalent std::thread
        // It would also create a new thread for each incoming
        // connection which would exhaust resources very quickly
        pthread_t connectionThread;
        pthread_create(&connectionThread, NULL, handleConnection, new Connection(incomingConnection));
    }
}