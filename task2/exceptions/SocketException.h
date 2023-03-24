#pragma once

#include <exception>
#include <string>

// Extends the existing exception to indicate its intent
// and that it will have the expected "what" member function
class SocketException : std::exception {
private:
    std::string reason;
    int errorNum;
public:
    SocketException(std::string reason);
    SocketException(std::string reason, int errorNum);
    std::string what();
};
