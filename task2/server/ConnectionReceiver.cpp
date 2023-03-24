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

ConnectionReceiver::ConnectionReceiver() {
    this->connections = std::set<Connection*>();
    this->onMessage = printMessage;
}

ConnectionReceiver::~ConnectionReceiver() {
    for (Connection* connection : connections) {
        delete connection;
    }
}

void ConnectionReceiver::add(Connection* connection) {    
    connections.insert(connection);
}

std::mutex handlingMessageMutex;
void handleConnection(Connection* connection, MessageFunction onMessage) {
    handlingMessageMutex.lock();
    std::string message = connection->receiveMessage();
    onMessage(connection, message);
    handlingMessageMutex.unlock();
}

void ConnectionReceiver::handleConnections() {
    while (true) {

        for (Connection* connection : connections) {
            if (!connection->hasPendingMessage()) continue;

            try {
                handleConnection(connection, onMessage);
            } catch(SocketException exception) {
                std::cout << "Received error when handling connection:\n\t" << exception.what() << std::endl;
                connections.erase(connection);
                delete connection;
                break;
            }
        }
    }
}

void ConnectionReceiver::start() {
    handlerThread = std::thread(&ConnectionReceiver::handleConnections, this);
}

void ConnectionReceiver::setOnMessage(MessageFunction function) {
    this->onMessage = function;
}
