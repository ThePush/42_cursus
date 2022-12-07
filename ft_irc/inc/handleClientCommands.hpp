#ifndef HANDLECLIENTCOMMANDS_HPP
#define HANDLECLIENTCOMMANDS_HPP

#pragma once

#include "Channel.hpp"
#include "TCPserver.hpp"
#include "User.hpp"
#include "include.hpp"

void handleClientCommands(User* user);
void handleWHOIS(User& user, std::vector<std::string> const& command);
void handlePING(User& user, std::vector<std::string> const& command);
void handleQUIT(User& user, std::vector<std::string> const& command);
void handleMODE(User* user, std::vector<std::string> const& command);
void handleUserMode(User* user, std::vector<std::string> const& command, bool isOperator);
void handleChannelMode(User* user, std::vector<std::string> const& command);
void handleJOIN(User& user, std::vector<std::string> const& command);
void handleTOPIC(User& user, std::vector<std::string> const& command);
void handlePRIVMSG(User& user, std::vector<std::string> const& command);
void privatePRIVMSG(User& user, std::vector<std::string> const& command);
void handleNOTICE(User& user, std::vector<std::string> const& command);
void privateNOTICE(User& user, std::vector<std::string> const& command);
void handlePART(User& user, std::vector<std::string> const& command);
void handleWHO(User* user, std::vector<std::string> const& command);
void changeNICK(User* user, std::string const& nickname);
void handleKICK(User& user, std::vector<std::string> const& command);
void handleINVITE(User& user, std::vector<std::string> const& command);
void handleLIST(User& user);
void handleKILL(User& user, std::vector<std::string> const& command);
void handleMOTD(User& user);
void handleLUSERS(User& user);
void handleOPER(User& user, std::vector<std::string> const& command);
void handleWALLOPS(User& user, std::vector<std::string> const& command);
void handleRESTART(User& user);

#endif // HANDLECLIENTCOMMANDS_HPP