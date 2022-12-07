#ifndef INCLUDE_HPP
#define INCLUDE_HPP

#include <algorithm> // fill_n
#include <arpa/inet.h> //close
#include <cstdlib>
#include <errno.h>
#include <exception>
#include <fcntl.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <netinet/in.h>
#include <poll.h>
#include <signal.h>
#include <sstream>
#include <stdexcept>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <utility>
#include <vector>

#include "rpl_codes.hpp"

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"
#define KYEL "\x1B[33m"
#define KBLU "\x1B[34m"
#define KMAG "\x1B[35m"
#define KCYN "\x1B[36m"
#define KWHT "\x1B[37m"

#define SERVER_NAME "nananirc" /* maximum 63 characters */
#define SERVER_VERSION "0.0.1"
#define SERVER_HOSTNAME "localhost"
#define SERVER_INFO "nananirc server"
#define SERVER_CHANNEL_MODES "ontkipsmlbv"
#define SERVER_USER_MODES "oiw" // https://www.mirc.com/help/html/index.html?basic_irc_commands.html
#define SERVER_ISUPPORT "NICKLEN=9 CHANNELLEN=50 TOPICLEN=50 CHANTYPES=# CHANMODES=nt"
#define MAX_MESSAGE_SIZE 509 // max message size = 509+':'+"\r\n" https://datatracker.ietf.org/doc/html/rfc1459#section-2.3
#define MAX_NICKNAME_SIZE 50
#define MAX_CHANNEL_SIZE 50
#define MAX_COMMAND_SIZE 16
#define TRUE 1
#define FALSE 0
#define DEBUG 0
#define PORT 30000
#define BUFFER_SIZE 1024
#define MAX_CLIENTS 50
#define SOCKET int
#define MAX_CONNECTIONS 50
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define INVALID_SOCKET ((int)-1)
#define ISACOMMAND(a) (a == "USER" || a == "PASS" || a == "CAP" || a == "WHOIS" || a == "PING" || a == "MODE" || a == "QUIT" || a == "JOIN" || a == "TOPIC" || a == "PRIVMSG" || a == "PART" || a == "WHO" || a == "MOTD" || a == "lusers" || a == "NICK" || a == "KICK" || a == "INVITE" || a == "motd" || a == "LIST" || a == "kill" || a == "PONG" || a == "OPER" || a == "wallops" || a == "restart" || a == "NOTICE")

#endif // INCLUDE_HPP