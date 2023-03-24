#include <sys/socket.h>
#include <arpa/inet.h>
#include "Comms.h"

Comms::Comms(const char* address, int port) {
    // Both the client and server need to have a socket
    // and similar address defined before listening/connecting
    this->socketFD = socket(AF_INET, SOCK_STREAM, 0);
    this->address = {
        .sin_family = AF_INET,
        .sin_port = htons(port),
        .sin_addr = { .s_addr = inet_addr(address) }
    };
}