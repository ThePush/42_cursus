#ifndef REGISTERUSER_HPP
#define REGISTERUSER_HPP

#pragma once

#include "Channel.hpp"
#include "TCPserver.hpp"
#include "User.hpp"
#include "include.hpp"

/* Registration */
void registerUser(User& user);
void handleCAP(User& user, std::vector<std::string> const& command);
void handlePASS(User& user, std::string const& password);
void handleNICK(User& user, std::string const& nickname);
void handleUSER(User& user, std::vector<std::string> const& command);
void sendWelcome(User& user);

#endif // REGISTERUSER_HPP