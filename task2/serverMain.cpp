#define IS_SERVER true

#include <iostream>
#include <string>
#include "server/Server.h"
#include "client/Client.h"
#include "exceptions/SocketException.h"

void messageReply(Connection* connection, std::string message) {
        std::cout << "Message received: " << message << "\nHow would you like to respond?" << std::endl;
        std::string response;
        std::getline(std::cin, response);
        connection->sendMessage(response);
}

int main() {
    char const *serverAddress = "127.0.0.1";
    int port = 3030;

    try {
#if IS_SERVER == true
        int maxConnections = 2;
        Server* server = new Server(serverAddress, port, maxConnections);
        server->setOnMessage(messageReply);
        server->start();
#else
        Client* client = new Client(serverAddress, port);
        bool shouldContinue = true;

        while (shouldContinue) {
            std::cout << "What message would you like to send?" << std::endl;
            std::string message;
            std::getline(std::cin, message);

            if (message == "QUIT") {
                shouldContinue = false;
                break;
            }

            client->send(message);

            std::cout << "Waiting for a response..." << std::endl;
            std::string response = client->receive();
            std::cout << "Response received: " << response << std::endl;
        }

        std::cout << "Closing session" << std::endl;
        delete client;
#endif
    } catch (SocketException exception) {
        std::cout << exception.what() << std::endl;
        return 1;
    }
}
