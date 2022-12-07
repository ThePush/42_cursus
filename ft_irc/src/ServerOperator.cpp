#include "../inc/ServerOperator.hpp"

ServerOperator::ServerOperator(std::string const& password, std::string const& nickname, std::string const& hostname)
    : _nickname(nickname), _password(password), _host(hostname) { }
ServerOperator::~ServerOperator() { }