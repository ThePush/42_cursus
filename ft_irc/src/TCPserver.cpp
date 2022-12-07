#include "../inc/TCPserver.hpp"

/* declaration of statics */
TCPsocket TCPserver::_master_socket;
std::vector<pollfd> TCPserver::_pfds;
std::map<int, User> TCPserver::_users;
std::vector<Channel*> TCPserver::_channels;
std::vector<ServerOperator> TCPserver::_serverOperators;
bool TCPserver::_restart = FALSE;
std::string TCPserver::_password = "";
TCPserver* TCPserver::_server = NULL;

TCPserver::TCPserver(int const& port, std::string const& password)
    : _port(port) {
    _password = password;
    _server = this;
    _serverOperators.push_back(ServerOperator());
}

TCPserver::~TCPserver() {
    for (std::map<int, User>::iterator it = _users.begin(); it != _users.end(); ++it) {
        close(it->first);
    }
    close(_master_socket.getFD());
    _users.clear();
    for (std::vector<Channel*>::iterator it = _channels.begin(); it != _channels.end(); ++it) {
        delete *it;
        *it = NULL;
    }
    _channels.clear();
    _pfds.clear();
    _serverOperators.clear();
}

/* Getters */
Channel* TCPserver::getChannel(std::string const& name) {
    for (std::vector<Channel*>::iterator it = _channels.begin(); it != _channels.end(); ++it) {
        if ((*it)->getName() == name)
            return *it;
    }
    return NULL;
}

User& TCPserver::getUser(int const& user_fd) {
    std::map<int, User>::iterator it = _users.find(user_fd);
    if (it != _users.end())
        return it->second;
    throw std::runtime_error("TCPserver::getUser(int const& user_fd) :User not found");
}

User& TCPserver::getUser(std::string const& nickname) {
    std::map<int, User>::iterator it = _users.begin();
    for (; it != _users.end(); it++) {
        if (it->second.getNickname() == nickname)
            return (it->second);
    }
    throw std::runtime_error("TCPserver::getUser(std::string const& nickname) :User not found");
}

/* Utils */
TCPserver& TCPserver::getServer() {
    if (_server == NULL)
        throw std::runtime_error("TCPserver::getServer() :Server not initialized");
    return *_server;
}

bool TCPserver::isChannelNameValid(std::string const& channelName) {
    if (channelName.length() < 2 || channelName.length() > MAX_CHANNEL_SIZE) return false;
    if (channelName[0] != '#' && channelName[0] != '&') return false;

    for (std::string::size_type i(1); i < channelName.length(); i++) {
        if (!std::isprint(channelName[i])
            || channelName[i] == ' '
            || channelName[i] == ',')
            return false;
    }
    return true;
}

bool TCPserver::isChannelNameTaken(std::string const& channelName) {
    for (std::vector<Channel*>::iterator it = _channels.begin(); it != _channels.end(); ++it) {
        if ((*it)->getName() == channelName)
            return true;
    }
    return false;
}

int TCPserver::receiveDatas(int const& user_fd) {
    int bytes_read = recv(_pfds[user_fd].fd, _buffer, sizeof(_buffer), 0);
    if (_buffer[0] == '\n') {
        return 0;
    }
    std::cout << displayTimestamp() << "[" << _pfds[user_fd].fd << "] [INCOMING] [" << bytes_read << "B]" << std::endl;
    if (bytes_read > 0 && _buffer[bytes_read - 1] != '\n') {
        std::cout << displayTimestamp() << "[" << _pfds[user_fd].fd << "] [INCOMING] [WARNING] Buffer not terminated with \\n"
                  << std::endl;
        std::cout << displayTimestamp() << "[" << _pfds[user_fd].fd << "] [INCOMING] [WARNING] Concatenating buffer" << std::endl;
        std::string tmp;
        if (bytes_read > BUFFER_SIZE - 1) {
            std::cout << displayTimestamp() << "[" << _pfds[user_fd].fd << "] [INCOMING] [WARNING] Buffer overflow" << std::endl;
            tmp = std::string(_buffer, BUFFER_SIZE - 2);
            tmp += "\n";
        }
        while ((bytes_read > 0 && bytes_read < 1023) && _buffer[bytes_read - 1] != '\n') {
            tmp = _buffer;
            memset(_buffer, 0, sizeof(_buffer));
            int tmp_bytes_read = bytes_read;
            bytes_read += recv(_pfds[user_fd].fd, _buffer, sizeof(_buffer), 0);
            if (bytes_read > BUFFER_SIZE - 1) {
                std::cout << displayTimestamp() << "[" << _pfds[user_fd].fd << "] [INCOMING] [WARNING] Buffer overflow" << std::endl;
                tmp = std::string(_buffer, BUFFER_SIZE - 1);
                tmp += "\n";
                break;
            }
            std::cout << displayTimestamp() << "[" << _pfds[user_fd].fd << "] [INCOMING] [" << bytes_read - tmp_bytes_read << "B]" << std::endl;
            if (tmp_bytes_read == bytes_read)
                break;
            tmp += _buffer;
            memset(_buffer, 0, sizeof(_buffer));
            strcpy(_buffer, tmp.c_str());
        }
    }
    return bytes_read;
}

/* core */
void TCPserver::runServer() {
/* Create a master_socket */
RESTART:
    TCPsocket master_socket(_port);
    _restart = FALSE;

    /* try to specify maximum of MAX_CONNECTIONS for the master socket */
    if (listen(master_socket.getFD(), MAX_CONNECTIONS) < 0) {
        perror("listen");
        throw std::runtime_error("TCPserver::runServer() :listen() failed");
    }
    std::cout << displayTimestamp() << "-!- [SERVER] Waiting for connections on port: [" << _port << "]" << std::endl;

    /* Client address */
    SOCKET new_sd;

    /* Initialize the pollfd structure */
    _pfds.push_back(pollfd());
    _pfds.back().fd = master_socket.getFD();
    _pfds.back().events = POLLIN;

    /* loop through all sockets and check which ones are ready to be read from */
    try {
        while (poll(_pfds.data(), _pfds.size(), -1) != -1) {
            /* print server info */
            std::cout << displayTimestamp() << "-!- [SERVER] Number of users connected: [" << _users.size() << "]" << std::endl;
            std::cout << displayTimestamp() << "-!- [SERVER] Number of channels created: [" << _channels.size() << "]" << std::endl;

            for (std::vector<pollfd>::size_type i(0); i < _pfds.size(); i++) {
                /* clear garbage in buffer */
                memset(_buffer, 0, BUFFER_SIZE);
                /* If socket is readable, handle data */
                if (_pfds[i].revents & POLLIN
                    || _pfds[i].revents & POLLHUP
                    || _pfds[i].revents & POLLERR
                    || _pfds[i].revents & POLLRDHUP) {
                    /* If master socket pfds[0] is readable, handle new connection */
                    if ((i == 0) && (_pfds[i].revents & POLLIN)) {
                        if ((new_sd = accept(master_socket.getFD(), NULL, NULL)) < 0) {
                            perror("accept failed");
                            break;
                        }
                        std::cout << displayTimestamp() << "[" << new_sd << "] [SERVER] New connection" << std::endl;
                        /* Add new connection to pollfd structure */
                        _pfds.push_back(pollfd());
                        _pfds.back().fd = new_sd;
                        _pfds.back().events = POLLIN;
                        /* Add new connection to user map */
                        _users[new_sd] = User(new_sd);
                    } else if (_pfds[i].revents & (POLLERR | POLLHUP | POLLRDHUP)) {
                        deleteUser(i);
                    } else {
                        /* Handle data from client */
                        int bytes_read = receiveDatas(i);
                        /* If connection is closed, close socket and remove from pollfd structure */
                        if (bytes_read <= 0) {
                            deleteUser(i);
                        } else {
                            /* If connection is open, handle data */
                            /* print buffer */
                            std::cout << displayTimestamp() << "[" << _pfds[i].fd << "] [INCOMING] " << _buffer;
                            /* Split buffer into user's _commands */
                            std::vector<std::string> commands = split(_buffer, "\r\n");
                            for (std::vector<std::string>::size_type j(0); j < commands.size(); j++) {
                                if (commands[j].size() > 0) {
                                    _users[_pfds[i].fd].addCommand(_users[_pfds[i].fd], commands[j]);
                                }
                            }
                            /* Print user's _commands for debugging purpose */
                            if (DEBUG) { _users[_pfds[i].fd].printCommands(); }
                            /* if user is not registered, handle registration */
                            if (!_users[_pfds[i].fd].isRegistered()) { registerUser(_users[_pfds[i].fd]); }
                            /* if user is registered and authenticated, handle client commands */
                            if (_users[_pfds[i].fd].isRegistered() && _users[_pfds[i].fd].isAuthenticated()) { handleClientCommands(&_users[_pfds[i].fd]); }
                            /* if user registration ended but authentication failed, close connection */
                            else if (_users[_pfds[i].fd].isRegistered() && !_users[_pfds[i].fd].isAuthenticated()) {
                                deleteUser(i);
                            }
                            if (_restart == TRUE) { goto RESTART; }
                            /* delete users killed */
                            if (_users.size() > 1 && _users[_pfds[i].fd].gotKilled()) {
                                for (std::vector<Channel>::size_type j(0); j < _channels.size(); j++) {
                                    _channels[j]->removeUser(&getUser(_pfds[i].fd));
                                }
                                close(_pfds[i].fd);
                                _users.erase(_pfds[i].fd);
                                _pfds.erase(_pfds.begin() + i);
                                continue;
                            }
                        }
                    }
                }
            }
            /* delete all empty channels */
            for (std::vector<Channel*>::iterator it = _channels.begin(); it != _channels.end();) {
                if ((*it)->getUsers().size() == 0) {
                    removeChannel((*it)->getName());
                } else {
                    ++it;
                }
            }
            std::cout << displayTimestamp() << "-!- [SERVER] Number of channels created: [" << _channels.size() << "]" << std::endl;
        }
    } catch (std::exception& e) {
        std::string reply = "ERROR: Server restarts: " + std::string(e.what()) + " (" + std::string(strerror(errno)) + ")\r\n";
        for (std::map<int, User>::iterator it = _users.begin(); it != _users.end(); ++it) {
            sendReply(it->second, reply);
        }
        goto RESTART;
    }
}

/**
 * Deletes a user from the server and prints infos to the console.
 *
 * @param i The index of the user to be deleted.
 */
void TCPserver::deleteUser(int const& i) {
    std::cout << displayTimestamp() << "[" << _pfds[i].fd << "] [SERVER] " << _users[_pfds[i].fd].getFullname() << " has disconnected." << std::endl;
    for (std::vector<Channel*>::iterator it = _channels.begin(); it != _channels.end(); it++) {
        (*it)->removeUser(&_users[_pfds[i].fd]);
    }
    _users.erase(_pfds[i].fd);
    close(_pfds[i].fd);
    _pfds.erase(_pfds.begin() + i);
    std::cout << displayTimestamp() << "-!- [SERVER] Number of users connected: [" << _users.size() << "]" << std::endl;
}

/**
 * Sends a reply to a user and prints infos on the server's console
 *
 * @param user The user to send the reply to.
 * @param reply The message to send to the user.
 */
void TCPserver::sendReply(User& user, std::string& reply) {
    std::string::size_type size(0);
    int bytesent(0);
    reply = reply.size() > MAX_MESSAGE_SIZE ? reply.substr(0, MAX_MESSAGE_SIZE) : reply;
    std::cout << displayTimestamp() << "[" << user.getFD() << "] [SENDING] " << reply;
    while (size < reply.size()) {
        if ((bytesent = send(user.getFD(), reply.c_str() + size, reply.size() - size, MSG_NOSIGNAL)) < 0)
            perror("send failed");
        size += bytesent;
    }
}

/**
 * Send the reply to all fd in the channel.
 *
 * @param reply The message to be sent to all users except the sender
 * @param users a map of all the users connected to the server
 * @param user The user who sent the message
 */
void TCPserver::broadcastMessage(std::string& reply, std::map<int, User*> users, User& user) {
    reply = reply.size() > MAX_MESSAGE_SIZE ? reply.substr(0, MAX_MESSAGE_SIZE) : reply;
    for (std::map<int, User*>::iterator it = users.begin(); it != users.end(); it++) {
        if (it->second->getFD() != user.getFD()) {
            sendReply(*it->second, reply);
        }
    }
}

/**
 * Remove a channel from the server.
 *
 * @param channelName The name of the channel to remove.
 */
void TCPserver::removeChannel(std::string const& channelName) {
    std::cout << displayTimestamp() << "-!- [SERVER] Removing channel: [" << channelName << "]" << std::endl;
    for (std::vector<Channel*>::iterator it = _channels.begin(); it != _channels.end(); it++) {
        if ((*it)->getName() == channelName) {
            delete *it;
            _channels.erase(it);
            break;
        }
    }
}