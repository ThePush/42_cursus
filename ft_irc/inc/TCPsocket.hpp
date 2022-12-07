#ifndef TCPSOCKET_HPP
#define TCPSOCKET_HPP

#pragma once

#include "include.hpp"

class TCPsocket {
public:
    TCPsocket(int const& port = PORT);
    ~TCPsocket();

    int getFD() const { return _socket; }

private:
    SOCKET _socket;
    struct sockaddr_in _address;
};

#endif // TCPSOCKET_HPP