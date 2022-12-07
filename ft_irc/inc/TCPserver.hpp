#ifndef TCPSERVER_HPP
#define TCPSERVER_HPP

#pragma once

#include "Channel.hpp"
#include "ChannelMode.hpp"
#include "ServerOperator.hpp"
#include "TCPsocket.hpp"
#include "User.hpp"
#include "handleClientCommands.hpp"
#include "include.hpp"
#include "registerUser.hpp"
#include "utils.hpp"

class Channel;
class User;

class TCPserver {
public:
    TCPserver(int const& port, std::string const& password);
    ~TCPserver();

    /* core */
    void runServer();

    /* Users */
    static void sendReply(User& user, std::string& reply);
    void deleteUser(int const& i);

    /* Getters */
    static Channel* getChannel(std::string const& name);
    static std::string& getPassword() { return _password; }
    static std::vector<Channel*>& getChannels() { return _channels; }
    static User& getUser(int const& user_fd);
    static User& getUser(std::string const& nickname);
    static std::map<int, User>& getUsers() { return _users; }
    static std::vector<pollfd>& getpfds() { return _pfds; }
    static bool& getRestart() { return _restart; }
    static TCPsocket& getSocket() { return _master_socket; }
    static std::vector<ServerOperator>& getServerOperators() { return _serverOperators; }
    static TCPserver& getServer();

    /* Setters */
    static void setRestart(bool const& restart) { _restart = restart; }

    /* Utils */
    static bool isChannelNameValid(std::string const& channelName);
    static bool isChannelNameTaken(std::string const& channelName);

    /* Methods */
    static void broadcastMessage(std::string& reply, std::map<int, User*> users, User& user);
    static void removeChannel(std::string const& channelName);
    int receiveDatas(int const& user_fd);

private:
    static TCPserver* _server;
    static TCPserver _instance;
    static TCPsocket _master_socket;
    static std::vector<pollfd> _pfds;
    static std::string _password;
    int _port;
    char _buffer[BUFFER_SIZE];
    static bool _restart;
    static std::map<int, User> _users;
    static std::vector<Channel*> _channels;
    static std::vector<ServerOperator> _serverOperators;
};

#endif // TCPSERVER_HPP