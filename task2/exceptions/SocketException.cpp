#include <iostream>
#include "SocketException.h"

// Overloading the constructor to allow the user to only
// pass a reason since an error number may not be available
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
