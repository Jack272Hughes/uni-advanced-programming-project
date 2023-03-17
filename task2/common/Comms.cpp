#include <sys/socket.h>
#include <arpa/inet.h>
#include "Comms.h"

Comms::Comms(const char* address, int port) {
    this->socketFD = socket(AF_INET, SOCK_STREAM, 0);
    this->address = {
        .sin_family = AF_INET,
        .sin_port = htons(port),
        .sin_addr = { .s_addr = inet_addr(address) }
    };
}