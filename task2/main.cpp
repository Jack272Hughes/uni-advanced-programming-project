#define IS_SERVER false

#include <iostream>
#include <string>
#include "server/Server.h"
#include "client/Client.h"
#include "exceptions/SocketException.h"

int main() {
    char const *serverAddress = "127.0.0.1";
    int port = 3030;

    try {
#if IS_SERVER == true
        int maxConnections = 1;

        Server* server = new Server(serverAddress, port);
        server->start(maxConnections);
#else
        Client* client = new Client(serverAddress, port);
        while (true) {
            std::cout << "What message would you like to send?" << std::endl;
            std::string message;
            std::getline(std::cin, message);
            client->send(message);
            std::string response = client->receive();
            std::cout << "Response received: " << response << std::endl;
        }
#endif
    } catch (SocketException exception) {
        std::cout << exception.what() << std::endl;
    }
}
