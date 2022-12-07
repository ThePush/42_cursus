#ifndef SERVEROPERATOR_HPP
#define SERVEROPERATOR_HPP

#pragma once

#include "include.hpp"

class ServerOperator {
public:
    ServerOperator(std::string const& password = "admin", std::string const& nickname = "admin", std::string const& hostname = "localhost");
    ~ServerOperator();

    /* Setters */
    void setOperator(std::string const& nickname, std::string const& password, std::string const& host) {
        _nickname = nickname;
        _password = password;
        _host = host;
    }

    /* Getters */
    std::string const& getNickname() const { return _nickname; }
    std::string const& getPassword() const { return _password; }
    std::string const& getHost() const { return _host; }

private:
    std::string _nickname;
    std::string _password;
    std::string _host;
};

#endif // SERVEROPERATOR_HPP