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
    this->connections = std::set<Connection*>();
    this->maxConnections = maxConnections;
    // Added a default on message function since the point of this
    // class in to receive messages and do something with them
    this->onMessage = printMessage;
}

ConnectionReceiver::~ConnectionReceiver() {
    for (Connection* connection : connections) {
        delete connection;
    }
}

void ConnectionReceiver::add(Connection* connection) {
    // Checks if we have reached the maximum number of connections
    // and deletes any that attempt to go over that limit
    if (connections.size() >= maxConnections) {
        std::cout << "Maximum number of connections reached, closing this connection" << std::endl;
        delete connection;
        return;
    }

    connections.insert(connection);
}

std::mutex handlingMessageMutex;
void handleConnection(Connection* connection, MessageFunction onMessage) {
    // A lock is added so that if we instantiate more than one
    // connection receiver then they will not clash with each other
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
                // Should an exception be thrown we should remove this connection as it is probably faulty
                // It will need to be removed from the connections set and deleted
                std::cout << "Received error when handling connection:\n\t" << exception.what() << std::endl;
                connections.erase(connection);
                delete connection;
                // We break out of the current for loop since we have just
                // removed an element from the set we're iterating over
                break;
            }
        }
    }
}

void ConnectionReceiver::start() {
    // Alternatively you could create a detached thread but it is
    // better to have a reference to a joinable instance of it
    handlerThread = std::thread(&ConnectionReceiver::handleConnections, this);
}

void ConnectionReceiver::setOnMessage(MessageFunction function) {
    this->onMessage = function;
}
