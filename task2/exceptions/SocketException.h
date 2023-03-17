#pragma once

#include <exception>
#include <string>

class SocketException : std::exception {
private:
    std::string reason;
    int errorNum;
public:
    SocketException(std::string reason);
    SocketException(std::string reason, int errorNum);
    std::string what();
};
