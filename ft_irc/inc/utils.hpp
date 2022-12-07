#ifndef UTILS_HPP
#define UTILS_HPP

#include "include.hpp"
#include "TCPserver.hpp"
#include "TCPsocket.hpp"
#include "User.hpp"

class User;

/* MAIN */
/* Check if the port is valid */
bool portIsValid(char* port);
/* Display date and time */
std::string displayTimestamp();

/* SERVER */
/* Split a string into a vector of strings */
std::vector<std::string> split(std::string const& str, std::string const& delim);
/* Check if nickname follows the rules */
bool isNicknameValid(std::string const& nickname);
/* Check if nickname is already taken */
bool isNicknameTaken(std::string const& nickname, std::map<int, User> const& user);
/* converts an integer into a string */
std::string toString(int const& i);


#endif // UTILS_HPP