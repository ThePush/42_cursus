#include "../inc/ChannelMode.hpp"

void handlek(TCPserver& server, std::vector<std::string> const& command, int add, Channel& channel, User* user) {
    (void)server;
    if (add) {
        if (command.size() > 3) {
            std::string key = command[3];
            channel.setMode('k', TRUE);
            channel.setKey(key);
            std::cout << displayTimestamp() << "-!- [CHANNEL " << channel.getName() << "] " << user->getNickname() << " set channel key to " << channel.getKey() << std::endl;
            //    std::string message = std::string(RPL_CHANNELMODEIS) + " MODE " + channel.getName() + " +" + channel.getMode() + " " + channel.getKey() + "\r\n";
            //    TCPserver::sendReply(*user, message);
            std::string message = ":" + user->getFullname() + " " + " MODE " + channel.getName() + " :+k " + key + "\r\n";
            TCPserver::sendReply(*user, message);
            TCPserver::broadcastMessage(message, channel.getUsers(), *user);
        } else {
            std::string message = std::string(ERR_NEEDMOREPARAMS) + " MODE MODE +k :Not enough parameters\r\n";
            TCPserver::sendReply(*user, message);
        }
    } else {
        channel.setMode('k', FALSE);
        std::cout << displayTimestamp() << "-!- [CHANNEL " << channel.getName() << "] " << user->getNickname() << " removed channel key: " << channel.getKey() << std::endl;
        //    std::string message = std::string(RPL_CHANNELMODEIS) + " MODE " + channel.getName() + " +" + channel.getMode() + " " + channel.getKey() + "\r\n";
        //    TCPserver::sendReply(*user, message);
        std::string message = ":" + user->getFullname() + " " + " MODE " + channel.getName() + " :-k " + channel.getKey() + "\r\n";
        TCPserver::sendReply(*user, message);
        TCPserver::broadcastMessage(message, channel.getUsers(), *user);
        channel.setKey("");
    }
}

void handlel(TCPserver& server, std::vector<std::string> const& command, int add, Channel& channel, User* user) {
    (void)server;
    if (add) {
        if (command.size() > 3) {
            int limit = atoi(command[3].c_str());
            if (command[3].find_first_not_of("0123456789") == std::string::npos && limit)
            {
                channel.setMode('l', TRUE);
                channel.setLimit(limit);
                std::cout << displayTimestamp() << "-!- [CHANNEL " << channel.getName() << "] " << user->getNickname() << " limited channel to " << channel.getLimit() << " users" << std::endl;
                //    std::string message = std::string(RPL_CHANNELMODEIS) + " MODE " + channel.getName() + " +" + channel.getMode() + " " + channel.getKey() + "\r\n";
                //    TCPserver::sendReply(*user, message);
                std::string message = ":" + user->getFullname() + " " + " MODE " + channel.getName() + " :+l " + toString(limit) + "\r\n";
                TCPserver::sendReply(*user, message);
                TCPserver::broadcastMessage(message, channel.getUsers(), *user);
            }
        } else {
            std::string message = std::string(ERR_NEEDMOREPARAMS) + " MODE MODE +l :Not enough parameters\r\n";
            TCPserver::sendReply(*user, message);
        }
    } else {
        channel.setMode('l', FALSE);
        std::cout << displayTimestamp() << "-!- [CHANNEL " << channel.getName() << "] " << user->getNickname() << " removed channel limit: " << channel.getLimit() << std::endl;
        //    std::string message = std::string(RPL_CHANNELMODEIS) + " MODE " + channel.getName() + " +" + channel.getMode() + " " + channel.getKey() + "\r\n";
        //    TCPserver::sendReply(*user, message);
        std::string message = ":" + user->getFullname() + " " + " MODE " + channel.getName() + " :-l " + toString(channel.getLimit()) + "\r\n";
        TCPserver::sendReply(*user, message);
        TCPserver::broadcastMessage(message, channel.getUsers(), *user);
        channel.setLimit(0);
    }
}

void handleo(TCPserver& server, std::vector<std::string> const& command, int add, Channel& channel, User* user) {
    if (add) {
        if (command.size() > 3) {
            std::string nickname = command[3];
            if (isNicknameTaken(nickname, server.getUsers())) {
                if (channel.isUserInChannel(server.getUser(nickname))) {
                    if (channel.isChannelOperator(&server.getUser(nickname)))
                        return;
                    channel.addOperator(&server.getUser(nickname));
                    std::cout << displayTimestamp() << "-!- [CHANNEL " << channel.getName() << "] " << user->getNickname() << " made " << nickname << " a channel operator" << std::endl;
                    // std::string message = std::string(RPL_CHANNELMODEIS) + " MODE " + channel.getName() + " +" + channel.getMode() + " " + channel.getKey() + "\r\n";
                    // TCPserver::sendReply(*user, message);
                    std::string message = ":" + user->getFullname() + " " + " MODE " + channel.getName() + " :+o " + nickname + "\r\n";
                    TCPserver::sendReply(*user, message);
                    TCPserver::broadcastMessage(message, channel.getUsers(), *user);
                } else {
                    std::string message = ":" + std::string(ERR_USERNOTINCHANNEL) + " " + nickname + " " + channel.getName() + " They aren't on that channel\r\n";
                    TCPserver::sendReply(*user, message);
                }
            } else {
                std::string message = ":" + std::string(ERR_NOSUCHNICK) + " " + nickname + ": No such nick/channel\r\n";
                TCPserver::sendReply(*user, message);
            }
        }
    } else {
        if (command.size() > 3) {
            std::string nickname = command[3];
            if (isNicknameTaken(nickname, server.getUsers())) {
                if (channel.isUserInChannel(server.getUser(nickname))) {
                    if (!channel.isChannelOperator(&server.getUser(nickname)))
                        return;
                    channel.removeOperator(&server.getUser(nickname));
                    std::cout << displayTimestamp() << "-!- [CHANNEL " << channel.getName() << "] " << user->getNickname() << " removed " << nickname << " from channel operators" << std::endl;
                    // std::string message = std::string(RPL_CHANNELMODEIS) + " MODE " + channel.getName() + " +" + channel.getMode() + " " + channel.getKey() + "\r\n";
                    // TCPserver::sendReply(*user, message);
                    std::string message = ":" + user->getFullname() + " " + " MODE " + channel.getName() + " :-o " + nickname + "\r\n";
                    TCPserver::sendReply(*user, message);
                    TCPserver::broadcastMessage(message, channel.getUsers(), *user);
                } else {
                    std::string message = ":" + std::string(ERR_USERNOTINCHANNEL) + " " + nickname + " " + channel.getName() + " They aren't on that channel\r\n";
                    TCPserver::sendReply(*user, message);
                }
            } else {
                std::string message = ":" + std::string(ERR_NOSUCHNICK) + " " + nickname + ": No such nick/channel\r\n";
                TCPserver::sendReply(*user, message);
            }
        }
    }
}

void handlev(TCPserver& server, std::vector<std::string> const& command, int add, Channel& channel, User* user) {
    if (add) {
        if (command.size() > 3) {
            std::string nickname = command[3];
            if (isNicknameTaken(nickname, server.getUsers())) {
                if (channel.isUserInChannel(server.getUser(nickname))) {
                    if (channel.isVoiced(&server.getUser(nickname)))
                        return;
                    channel.addVoiced(&server.getUser(nickname));
                    std::cout << displayTimestamp() << "-!- [CHANNEL " << channel.getName() << "] " << user->getNickname() << " gave voice to " << nickname << std::endl;
                    // std::string message = std::string(RPL_CHANNELMODEIS) + " MODE " + channel.getName() + " +" + channel.getMode() + " " + channel.getKey() + "\r\n";
                    // TCPserver::sendReply(*user, message);
                    std::string message = ":" + user->getFullname() + " " + " MODE " + channel.getName() + " :+v " + nickname + "\r\n";
                    TCPserver::sendReply(*user, message);
                    TCPserver::broadcastMessage(message, channel.getUsers(), *user);
                } else {
                    std::string message = ":" + std::string(ERR_USERNOTINCHANNEL) + " " + nickname + " " + channel.getName() + " They aren't on that channel\r\n";
                    TCPserver::sendReply(*user, message);
                }
            } else {
                std::string message = ":" + std::string(ERR_NOSUCHNICK) + " " + nickname + ": No such nick/channel\r\n";
                TCPserver::sendReply(*user, message);
            }
        }
    } else {
        if (command.size() > 3) {
            std::string nickname = command[3];
            if (isNicknameTaken(nickname, server.getUsers())) {
                if (channel.isUserInChannel(server.getUser(nickname))) {
                    if (!channel.isVoiced(&server.getUser(nickname)))
                        return;
                    channel.removeVoiced(&server.getUser(nickname));
                    std::cout << displayTimestamp() << "-!- [CHANNEL " << channel.getName() << "] " << user->getNickname() << " removed voice from " << nickname << std::endl;
                    // std::string message = std::string(RPL_CHANNELMODEIS) + " MODE " + channel.getName() + " +" + channel.getMode() + " " + channel.getKey() + "\r\n";
                    // TCPserver::sendReply(*user, message);
                    std::string message = ":" + user->getFullname() + " " + " MODE " + channel.getName() + " :-v " + nickname + "\r\n";
                    TCPserver::sendReply(*user, message);
                    TCPserver::broadcastMessage(message, channel.getUsers(), *user);
                } else {
                    std::string message = ":" + std::string(ERR_USERNOTINCHANNEL) + " " + nickname + " " + channel.getName() + " They aren't on that channel\r\n";
                    TCPserver::sendReply(*user, message);
                }
            } else {
                std::string message = ":" + std::string(ERR_NOSUCHNICK) + " " + nickname + ": No such nick/channel\r\n";
                TCPserver::sendReply(*user, message);
            }
        }
    }
}

void handleb(TCPserver& server, std::vector<std::string> const& command, int add, Channel& channel, User* user) {
    if (command.size() > 3) {
        std::string maskname = command[3];
        if (add) {
            if (channel.isBanned(maskname) || maskname.find_first_of('@') != maskname.find_last_of('@') || maskname.find('@') == std::string::npos)
                return;
            for (std::map<int, User>::iterator it = server.getUsers().begin(); it != server.getUsers().end(); it++)
                if (maskname == it->second.getNickname())
                    maskname = it->second.getFullname();
            channel.addBan(maskname, user);
            std::cout << displayTimestamp() << "-!- [CHANNEL " << channel.getName() << "] " << user->getNickname() << " banned " << maskname << std::endl;
            // std::string message = std::string(RPL_CHANNELMODEIS) + " MODE " + channel.getName() + " +" + channel.getMode() + " " + channel.getKey() + "\r\n";
            // TCPserver::sendReply(*user, message);
            std::string message = ":" + user->getFullname() + " " + " MODE " + channel.getName() + " :+b " + maskname + "\r\n";
            TCPserver::sendReply(*user, message);
            TCPserver::broadcastMessage(message, channel.getUsers(), *user);
        } else {
            if (channel.isBanned(maskname)) {
                channel.removeBan(maskname);
                std::cout << displayTimestamp() << "-!- [CHANNEL " << channel.getName() << "] " << user->getNickname() << " removed ban from " << maskname << std::endl;
                // std::string message = std::string(RPL_CHANNELMODEIS) + " MODE " + channel.getName() + " +" + channel.getMode() + " " + channel.getKey() + "\r\n";
                // TCPserver::sendReply(*user, message);
                std::string message = ":" + user->getFullname() + " " + " MODE " + channel.getName() + " :-b " + maskname + "\r\n";
                TCPserver::sendReply(*user, message);
                TCPserver::broadcastMessage(message, channel.getUsers(), *user);
            }
        }
    } else {
        std::string message;
        for (size_t i = 0; i < channel.getBans().size(); i++) {
            message = std::string(RPL_BANLIST) + " " + channel.getName() + " " +  channel.getBans()[i]->getMaskName() + " " + channel.getBans()[i]->getUser() + " " + toString(channel.getBans()[i]->getTime()) + "\r\n";
            TCPserver::sendReply(*user, message);
        }
        message = std::string(RPL_ENDOFBANLIST) + " " + channel.getName() + " : End of channel ban list\r\n";
        TCPserver::sendReply(*user, message);

    }
}

void handlei(TCPserver& server, std::vector<std::string> const& command, int add, Channel& channel, User* user) {
    (void)server;
    (void)command;
    if (add) {
        channel.setMode('i', TRUE);
        std::cout << displayTimestamp() << "-!- [CHANNEL " << channel.getName() << "] " << user->getNickname() << " set channel to invite only" << std::endl;
        // std::string message = std::string(RPL_CHANNELMODEIS) + " MODE " + channel.getName() + " +" + channel.getMode() + " " + channel.getKey() + "\r\n";
        // TCPserver::sendReply(*user, message);
        std::string message = ":" + user->getFullname() + " " + " MODE " + channel.getName() + " :+i\r\n";
        TCPserver::sendReply(*user, message);
        TCPserver::broadcastMessage(message, channel.getUsers(), *user);
    } else {
        channel.setMode('i', FALSE);
        std::cout << displayTimestamp() << "-!- [CHANNEL " << channel.getName() << "] " << user->getNickname() << " removed channel's invite only mode" << std::endl;
        // std::string message = std::string(RPL_CHANNELMODEIS) + " MODE " + channel.getName() + " +" + channel.getMode() + " " + channel.getKey() + "\r\n";
        // TCPserver::sendReply(*user, message);
        std::string message = ":" + user->getFullname() + " " + " MODE " + channel.getName() + " :-i\r\n";
        TCPserver::sendReply(*user, message);
        TCPserver::broadcastMessage(message, channel.getUsers(), *user);
    }
}

void handlem(TCPserver& server, std::vector<std::string> const& command, int add, Channel& channel, User* user) {
    (void)server;
    (void)command;
    if (add) {
        channel.setMode('m', TRUE);
        std::cout << displayTimestamp() << "-!- [CHANNEL " << channel.getName() << "] " << user->getNickname() << " set channel to moderated" << std::endl;
        // std::string message = std::string(RPL_CHANNELMODEIS) + " MODE " + channel.getName() + " +" + channel.getMode() + " " + channel.getKey() + "\r\n";
        // TCPserver::sendReply(*user, message);
        std::string message = ":" + user->getFullname() + " " + " MODE " + channel.getName() + " :+m\r\n";
        TCPserver::sendReply(*user, message);
        TCPserver::broadcastMessage(message, channel.getUsers(), *user);
    } else {
        channel.setMode('m', FALSE);
        std::cout << displayTimestamp() << "-!- [CHANNEL " << channel.getName() << "] " << user->getNickname() << " removed channel's moderated mode" << std::endl;
        // std::string message = std::string(RPL_CHANNELMODEIS) + " MODE " + channel.getName() + " +" + channel.getMode() + " " + channel.getKey() + "\r\n";
        // TCPserver::sendReply(*user, message);
        std::string message = ":" + user->getFullname() + " " + " MODE " + channel.getName() + " :-m\r\n";
        TCPserver::sendReply(*user, message);
        TCPserver::broadcastMessage(message, channel.getUsers(), *user);
    }
}

void handlen(TCPserver& server, std::vector<std::string> const& command, int add, Channel& channel, User* user) {
    (void)server;
    (void)command;
    if (add) {
        channel.setMode('n', TRUE);
        std::cout << displayTimestamp() << "-!- [CHANNEL " << channel.getName() << "] " << user->getNickname() << " set channel to no external message" << std::endl;
        // std::string message = std::string(RPL_CHANNELMODEIS) + " MODE " + channel.getName() + " +" + channel.getMode() + " " + channel.getKey() + "\r\n";
        // TCPserver::sendReply(*user, message);
        std::string message = ":" + user->getFullname() + " " + " MODE " + channel.getName() + " :+n\r\n";
        TCPserver::sendReply(*user, message);
        TCPserver::broadcastMessage(message, channel.getUsers(), *user);
    } else {
        channel.setMode('n', FALSE);
        std::cout << displayTimestamp() << "-!- [CHANNEL " << channel.getName() << "] " << user->getNickname() << " removed channel's no external message mode" << std::endl;
        // std::string message = std::string(RPL_CHANNELMODEIS) + " MODE " + channel.getName() + " +" + channel.getMode() + " " + channel.getKey() + "\r\n";
        // TCPserver::sendReply(*user, message);
        std::string message = ":" + user->getFullname() + " " + " MODE " + channel.getName() + " :-n\r\n";
        TCPserver::sendReply(*user, message);
        TCPserver::broadcastMessage(message, channel.getUsers(), *user);
    }
}

void handlep(TCPserver& server, std::vector<std::string> const& command, int add, Channel& channel, User* user) {
    (void)server;
    (void)command;
    if (add) {
        channel.setMode('p', TRUE);
        std::cout << displayTimestamp() << "-!- [CHANNEL " << channel.getName() << "] " << user->getNickname() << " set channel to lock topic" << std::endl;
        // std::string message = std::string(RPL_CHANNELMODEIS) + " MODE " + channel.getName() + " +" + channel.getMode() + " " + channel.getKey() + "\r\n";
        // TCPserver::sendReply(*user, message);
        std::string message = ":" + user->getFullname() + " " + " MODE " + channel.getName();
        if (channel.getMode().find('s') != std::string::npos) {
            channel.setMode('s', FALSE);
            message += " :-s+p\r\n";
        } else {
            message += " :+p\r\n";
        }
        TCPserver::sendReply(*user, message);
        TCPserver::broadcastMessage(message, channel.getUsers(), *user);
    } else {
        channel.setMode('p', FALSE);
        std::cout << displayTimestamp() << "-!- [CHANNEL " << channel.getName() << "] " << user->getNickname() << " removed channel's to lock topic mode" << std::endl;
        // std::string message = std::string(RPL_CHANNELMODEIS) + " MODE " + channel.getName() + " +" + channel.getMode() + " " + channel.getKey() + "\r\n";
        // TCPserver::sendReply(*user, message);
        std::string message = ":" + user->getFullname() + " " + " MODE " + channel.getName() + " :-p\r\n";
        TCPserver::sendReply(*user, message);
        TCPserver::broadcastMessage(message, channel.getUsers(), *user);
    }
}

void handles(TCPserver& server, std::vector<std::string> const& command, int add, Channel& channel, User* user) {
    (void)server;
    (void)command;
    if (add) {
        channel.setMode('s', TRUE);
        std::cout << displayTimestamp() << "-!- [CHANNEL " << channel.getName() << "] " << user->getNickname() << " set channel to lock topic" << std::endl;
        // std::string message = std::string(RPL_CHANNELMODEIS) + " MODE " + channel.getName() + " +" + channel.getMode() + " " + channel.getKey() + "\r\n";
        // TCPserver::sendReply(*user, message);
        std::string message = ":" + user->getFullname() + " " + " MODE " + channel.getName();
        if (channel.getMode().find('p') != std::string::npos) {
            channel.setMode('p', FALSE);
            message += " :-p+s\r\n";
        } else {
            message += " :+s\r\n";
        }
        TCPserver::sendReply(*user, message);
        TCPserver::broadcastMessage(message, channel.getUsers(), *user);
    } else {
        channel.setMode('s', FALSE);
        std::cout << displayTimestamp() << "-!- [CHANNEL " << channel.getName() << "] " << user->getNickname() << " removed channel's to lock topic mode" << std::endl;
        // std::string message = std::string(RPL_CHANNELMODEIS) + " MODE " + channel.getName() + " +" + channel.getMode() + " " + channel.getKey() + "\r\n";
        // TCPserver::sendReply(*user, message);
        std::string message = ":" + user->getFullname() + " " + " MODE " + channel.getName() + " :-s\r\n";
        TCPserver::sendReply(*user, message);
        TCPserver::broadcastMessage(message, channel.getUsers(), *user);
    }
}

void handlet(TCPserver& server, std::vector<std::string> const& command, int add, Channel& channel, User* user) {
    (void)server;
    (void)command;
    if (add) {
        channel.setMode('t', TRUE);
        std::cout << displayTimestamp() << "-!- [CHANNEL " << channel.getName() << "] " << user->getNickname() << " set channel to no external message" << std::endl;
        // std::string message = std::string(RPL_CHANNELMODEIS) + " MODE " + channel.getName() + " +" + channel.getMode() + " " + channel.getKey() + "\r\n";
        // TCPserver::sendReply(*user, message);
        std::string message = ":" + user->getFullname() + " " + " MODE " + channel.getName() + " :+t\r\n";
        TCPserver::sendReply(*user, message);
        TCPserver::broadcastMessage(message, channel.getUsers(), *user);
    } else {
        channel.setMode('t', FALSE);
        std::cout << displayTimestamp() << "-!- [CHANNEL " << channel.getName() << "] " << user->getNickname() << " removed channel's no external message mode" << std::endl;
        // std::string message = std::string(RPL_CHANNELMODEIS) + " MODE " + channel.getName() + " +" + channel.getMode() + " " + channel.getKey() + "\r\n";
        // TCPserver::sendReply(*user, message);
        std::string message = ":" + user->getFullname() + " " + " MODE " + channel.getName() + " :-t\r\n";
        TCPserver::sendReply(*user, message);
        TCPserver::broadcastMessage(message, channel.getUsers(), *user);
    }
}

ChannelMode::ChannelMode(TCPserver& server, std::vector<std::string> const& command, Channel& channel, User* user) {
    try {
        std::string mode = command[2];
        if ((mode[0] == '+' || mode[0] == '-') && !channel.isChannelOperator(user)) {
            throw CHANOPRIVSNEEDEDExeption();
        }
        if (mode[0] == '+')
            _add = 1;
        if (mode[0] == '-')
            _add = 0;
        char key[] = { 'k', 'i', 'o', 'v', 'm', 'n', 't', 'p', 's', 'l', 'b' };
        fptr value[] = { handlek, handlei, handleo, handlev, handlem, handlen, handlet, handlep, handles, handlel, handleb };
        for (int i = 0; i < 11; i++)
            _mapmodes.insert(std::pair<char, fptr>(key[i], value[i]));
        for (std::string::size_type i(1); i < mode.size(); i++) {
            try {
                if (std::string(SERVER_CHANNEL_MODES).find(mode[i]) == std::string::npos)
                    throw UMODEUNKNOWNFLAGExeption();
                std::map<char, fptr>::iterator it = _mapmodes.find(mode[i]);
                if (mode[i] == 'o' || mode[i] == 'v' || mode[i] == 'b' || ((((channel.getMode().find(mode[i]) == std::string::npos) || mode[i] == 'l') && mode[0] == '+') || ((channel.getMode().find(mode[i]) != std::string::npos) && mode[0] == '-')))
                    it->second(server, command, _add, channel, user);
            } catch (UMODEUNKNOWNFLAGExeption& e) {
                std::string message = std::string(e.what()) + " " + user->getNickname() + " :Unknown MODE flag\r\n";
                TCPserver::sendReply(*user, message);
            }
        }
    } catch (CHANOPRIVSNEEDEDExeption& e) {
        std::string message = std::string(e.what()) + " " + channel.getName() + " :You're not channel operator\r\n";
        TCPserver::sendReply(*user, message);
    }
}

ChannelMode::~ChannelMode() { _mapmodes.clear(); }