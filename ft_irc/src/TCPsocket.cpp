#include "../inc/TCPsocket.hpp"

TCPsocket::TCPsocket(int const& port) {
    /* Create a socket */
    if ((_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        throw std::runtime_error("TCPsocket::socket() :Socket creation error");
    }

    /* Allow socket descriptor to be reuseable */
    const int opt(1);
    if (setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt)) < 0) {
        close(_socket);
        throw std::runtime_error("TCPsocket::setsockopt() :error");
    }

    /* Set socket to non-blocking */
    if (fcntl(_socket, F_SETFL, O_NONBLOCK) < 0) {
        close(_socket);
        throw std::runtime_error("TCPsocket::fcntl() :error");
    }

    /* Set up address structure */
    memset(&_address, 0, sizeof(_address));
    _address.sin_family = AF_INET;
    _address.sin_addr.s_addr = INADDR_ANY;
    _address.sin_port = htons(port);

    /* Bind the file descriptor to the address */
    if (bind(_socket, (struct sockaddr*)&_address, sizeof(_address)) < 0) {
        close(_socket);
        throw std::runtime_error("TCPsocket::bind() :error");
    }
}

TCPsocket::~TCPsocket() {
    /* Shutdown all connections */
    shutdown(_socket, SHUT_RDWR);
    /* Close the socket */
    close(_socket);
}