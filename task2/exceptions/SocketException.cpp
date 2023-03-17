#include <iostream>
#include "SocketException.h"

SocketException::SocketException(std::string reason) {
    this->reason = reason;
}

SocketException::SocketException(std::string reason, int errorNum) {
    this->reason = reason;
    this->errorNum = errorNum;
}

std::string SocketException::what() {
    std::string message = "SocketException: " + this->reason;
    if (errorNum) {
        message += "\n  Caused by: " + std::string(strerror(errorNum));
    }
    return message;
}
