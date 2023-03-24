#include <iostream>
#include <unistd.h>
#include <thread>
#include <mutex>
#include <algorithm>
#include "ConnectionReceiver.h"
#include "exceptions/SocketException.h"

void printMessage(Connection* connection, std::string message) {
    std::cout << "Message received: " << message << std::endl;
}

ConnectionReceiver::ConnectionReceiver(int maxConnections) {
    this->connections = new Connection*[maxConnections];
    this->totalConnections = 0;
    this->onMessage = printMessage;
}

ConnectionReceiver::~ConnectionReceiver() {
    for (int index = 0; index < totalConnections; index++) {
        delete connections[index];
    }
    delete[] connections;
}

void ConnectionReceiver::add(Connection* connection) {
    if (totalConnections >= sizeof(connections)) {
        std::cout << "Maximum number of connections reached, closing this connection" << std::endl;
        delete connection;
    }
    
    connections[totalConnections] = connection;
    totalConnections++;
}

std::mutex handlingMessageMutex;
void handleConnection(Connection* connection, MessageFunction onMessage) {
    handlingMessageMutex.lock();

    try {
        std::string message = connection->receiveMessage();
        onMessage(connection, message);
    } catch(SocketException exception) {
        std::cout << "Received error when handling connection:\n" << exception.what() << std::endl;
    }

    handlingMessageMutex.unlock();
}

void ConnectionReceiver::handleConnections() {
    while (true) {
        for (int index = 0; index < totalConnections; index++) {
            Connection* connection = this->connections[index];
            if (!connection->hasPendingMessage()) continue;
            handleConnection(connection, onMessage);
        }
    }
}

void ConnectionReceiver::start() {
    handlerThread = std::thread(&ConnectionReceiver::handleConnections, this);
}

void ConnectionReceiver::setOnMessage(MessageFunction function) {
    this->onMessage = function;
}
