#include "../inc/handleClientCommands.hpp"

/**
 * WHOIS command:
 * https://modern.ircdocs.horse/#whois-message
 *
 * @param user a reference to the user object that is currently connected to the server
 * @param command a vector of strings, where each string is a word in the command.
 */
void handleWHOIS(User& user, std::vector<std::string> const& command) {
    if (command.size() > 1) {
        std::string target = "";
        /* if first arg is the server name and second arg is target */
        if (command[1] == SERVER_NAME && command.size() > 2) {
            target = command[2];
        }
        /* if first arg is target */
        else if (command[1] != SERVER_NAME) {
            target = command[1];
        }
        if (target.size() > 0) {
            /* check if target is valid */
            if (isNicknameValid(target)) {
                /* check if target is taken */
                if (isNicknameTaken(target, TCPserver::getUsers())) {
                    /* send WHOIS reply */
                    User& tuser = TCPserver::getUser(target);
                    std::vector<Channel*> channelptr = tuser.getUserChannels();
                    std::string message = std::string(RPL_WHOISUSER) + " " + tuser.getNickname() + " " + tuser.getNickname() + " " + tuser.getUsername() + " " + tuser.getHostname() + " * :" + tuser.getRealName() + "\r\n";
                    TCPserver::sendReply(user, message);
                    message = std::string(RPL_WHOISCHANNEL) + " " + tuser.getNickname() + " " + tuser.getNickname() + " :";
                    for (std::vector<Channel*>::iterator it = channelptr.begin(); it != channelptr.end(); it++) {
                        if (((*it)->getMode().find('p') == std::string::npos && (*it)->getMode().find('s') == std::string::npos) || (*it)->isUserInChannel(tuser)) {
                            if ((*it)->isChannelOperator(&tuser))
                                message += " @" + (*it)->getName();
                            else if ((*it)->isVoiced(&tuser))
                                message += " +" + (*it)->getName();
                            else
                                message += "  " + (*it)->getName();
                        }
                    }
                    message += "\r\n";
                    TCPserver::sendReply(user, message);
                    message = std::string(RPL_WHOISSERVER) + " " + tuser.getNickname() + " " + tuser.getNickname() + " " + SERVER_NAME + " :" + SERVER_VERSION + "\r\n";
                    TCPserver::sendReply(user, message);
                    message = std::string(RPL_ENDOFWHOIS) + " " + tuser.getNickname() + " " + tuser.getNickname() + " :End of WHOIS list\r\n";
                    TCPserver::sendReply(user, message);
                } else {
                    /* if target is not taken, send error message */
                    std::string message = std::string(ERR_NOSUCHNICK) + " " + target + " : No such nick/channel\r\n";
                    TCPserver::sendReply(user, message);
                }
            } else {
                /* if target is not valid, send error message */
                std::string message = std::string(ERR_ERRONEUSNICKNAME) + " " + target + " : Erroneous nickname\r\n";
                TCPserver::sendReply(user, message);
            }
        } else {
            /* if nickname is empty, send error message */
            std::string message = std::string(ERR_NONICKNAMEGIVEN) + " : No nickname given\r\n";
            TCPserver::sendReply(user, message);
        }
    } else {
        /* if command is empty, send error message */
        std::string message = std::string(ERR_NEEDMOREPARAMS) + " : Not enough parameters\r\n";
        TCPserver::sendReply(user, message);
    }
    user.deleteCommand("WHOIS");
}

/**
 * PING command:
 * https://modern.ircdocs.horse/#ping-message
 *
 * @param user The user who sent the command.
 * @param command The command that was sent by the user.
 */
void handlePING(User& user, std::vector<std::string> const& command) {
    if (command.size() > 1) {
        std::string reply = "PONG " + command[1] + "\r\n";
        TCPserver::sendReply(user, reply);
    } else {
        std::string message = std::string(ERR_NEEDMOREPARAMS) + " : ERROR :No origin specified\r\n";
        TCPserver::sendReply(user, message);
    }
    user.deleteCommand("PING");
}

/**
 * Handles the user part of the MODE command.
 *
 * @param user The user who sent the command
 * @param command a vector of strings, where each string is a word in the command
 */
void handleUserMode(User* user, std::vector<std::string> const& command, bool isOperator) {
    if (command.size() > 2 && command[2].size() > 1) {
        std::string mode = command[2];
        if (mode[0] == '+') {
            for (std::string::size_type i(1); i < mode.size(); i++) {
                if (std::string(SERVER_USER_MODES).find(mode[i]) == std::string::npos) {
                    std::string message = std::string(ERR_UMODEUNKNOWNFLAG) + " " + user->getNickname() + " :Unknown MODE flag\r\n";
                    TCPserver::sendReply(*user, message);
                } else {
                    if (mode[i] == 'o') {
                        if (user->isServerOperator() || isOperator == TRUE) {
                            user->setMode(mode[i], TRUE);
                            std::string message = ":" + std::string(RPL_YOUREOPER) + " You are now an IRC operator\r\n";
                            TCPserver::sendReply(*user, message);
                        } else {
                            std::string message = std::string(ERR_NOPRIVILEGES) + " " + user->getNickname() + " :Permission Denied- You're not an IRC operator\r\n";
                            TCPserver::sendReply(*user, message);
                            return;
                        }
                    } else {
                        user->setMode(mode[i], TRUE);
                    }
                }
            }
        } else if (mode[0] == '-') {
            for (std::string::size_type i(1); i < mode.size(); i++) {
                if (std::string(SERVER_USER_MODES).find(mode[i]) == std::string::npos) {
                    std::string message = std::string(ERR_UMODEUNKNOWNFLAG) + " " + user->getNickname() + " :Unknown MODE flag\r\n";
                    TCPserver::sendReply(*user, message);
                } else {
                    if (mode[i] == 'o') {
                        user->setMode(mode[i], FALSE);
                        user->setServerOperator(FALSE);
                        std::string message = ":" + std::string(RPL_YOUREOPER) + " You are no longer an IRC operator\r\n";
                        TCPserver::sendReply(*user, message);
                    } else {
                        user->setMode(mode[i], FALSE);
                    }
                }
            }
        }
    } else {
        std::string message = std::string(ERR_NEEDMOREPARAMS) + " :Not enough parameters\r\n";
        TCPserver::sendReply(*user, message);
    }
    std::string reply = std::string(RPL_UMODEIS) + " " + user->getNickname() + " " + user->getMode() + "\r\n";
    TCPserver::sendReply(*user, reply);
}

/**
 * Handles the channel part of the MODE command.
 *
 * @param user The user who sent the command.
 * @param command the command that was sent to the server
 */
void handleChannelMode(User* user, std::vector<std::string> const& command) {
    std::string target = command[1];
    Channel* channel = TCPserver::getChannel(target);
    if (command.size() > 2) {
        ChannelMode channelMode(TCPserver::getServer(), command, *channel, user);
    } else {
        std::string message = std::string(RPL_CHANNELMODEIS) + " MODE " + channel->getName() + " " + channel->getMode() + " ";
        if (channel->getLimit())
            message += toString(channel->getLimit()) + " ";
        message += channel->getKey() + "\r\n";
        TCPserver::sendReply(*user, message);
    }
}

/**
 * MODE command:
 * https://modern.ircdocs.horse/#mode-message
 *
 * @param user The user who sent the command.
 * @param command a vector of strings, where each string is a word in the command.
 *
 */
void handleMODE(User* user, std::vector<std::string> const& command) {
    if (command.size() > 1) {
        std::string target = command[1];
        if (target.size() > 0 && target[0] == '#') {
            if (target.size() > 1) {
                if (TCPserver::isChannelNameValid(target) && TCPserver::isChannelNameTaken(target)) {
                    handleChannelMode(user, command);
                } else {
                    std::string message = std::string(ERR_NOSUCHCHANNEL) + " " + user->getNickname() + " " + target + " :No such channel\r\n";
                    TCPserver::sendReply(*user, message);
                }
            } else {
                std::string message = std::string(ERR_NEEDMOREPARAMS) + " " + user->getNickname() + " :Not enough parameters\r\n";
                TCPserver::sendReply(*user, message);
            }
        } else {
            if (target.size() > 0) {
                if (isNicknameTaken(target, TCPserver::getUsers())) {
                    if (command.size() > 2) {
                        if (target == user->getNickname()) {
                            handleUserMode(user, command, FALSE);
                        } else if (target != user->getNickname() && user->getMode().find('o') != std::string::npos) {
                            handleUserMode(&TCPserver::getUser(target), command, TRUE);
                        } else {
                            std::string message = std::string(ERR_USERSDONTMATCH) + " " + user->getNickname() + " :Cannot change mode for other users\r\n";
                            TCPserver::sendReply(*user, message);
                        }
                    } else {
                        std::string message = std::string(ERR_NEEDMOREPARAMS) + " " + user->getNickname() + " :Not enough parameters\r\n";
                        TCPserver::sendReply(*user, message);
                    }
                } else {
                    std::string message = std::string(ERR_NOSUCHNICK) + " " + user->getNickname() + " " + target + " :No such nick\r\n";
                    TCPserver::sendReply(*user, message);
                }
            } else {
                std::string message = std::string(ERR_NEEDMOREPARAMS) + " " + user->getNickname() + " :Not enough parameters\r\n";
                TCPserver::sendReply(*user, message);
            }
        }
    } else {
        std::string message = std::string(ERR_NEEDMOREPARAMS) + " " + user->getNickname() + " :Not enough parameters\r\n";
        TCPserver::sendReply(*user, message);
    }
    user->deleteCommand("MODE");
}

/**
 * QUIT command:
 * https://modern.ircdocs.horse/#quit-message
 *
 * @param user The user who sent the command
 * @param command a vector of strings, where each string is a word in the command
 */
void handleQUIT(User& user, std::vector<std::string> const& command) {
    if (command.size() > 1) {
        std::string reason;
        if (command.size() > 2) {
            for (size_t i = 1; i < command.size(); i++) {
                if (i != command.size() - 1) {
                    reason += command[i] + " ";
                } else {
                    reason += command[i];
                }
            }
        } else {
            reason = command[1];
        }
        std::string reply = ":" + user.getFullname() + " QUIT " + reason + "\r\n";
        user.deleteCommand("QUIT");
        TCPserver::sendReply(user, reply);
    }
}

/**
 * JOIN command:
 *
 * https://modern.ircdocs.horse/#join-message
 *
 * @param user The user who sent the command
 * @param command a vector of strings, where each string is a word in the command.
 */
void handleJOIN(User& user, std::vector<std::string> const& command) {
    if (command.size() > 1) {
        std::string channel_name = command[1];
        if (channel_name.size() > 0) {
            /* split command in case several channel names has been entered */
            std::vector<std::string> channelsToJoin = split(channel_name, ",");
            /* split command to store keys */
            std::vector<std::string> keys;
            if (command.size() > 2) { keys = split(command[2], ","); }
            for (std::string::size_type i(0); i < channelsToJoin.size(); i++) {
                if (TCPserver::isChannelNameValid(channelsToJoin[i])) {
                    if (TCPserver::isChannelNameTaken(channelsToJoin[i])) {
                        Channel* channelPtr = TCPserver::getChannel(channelsToJoin[i]);
                        if (!channelPtr->isUserInChannel(user)) {
                            if (!channelPtr->isBanned(user.getFullname())) {
                                /* if channel has mode 'i' and user is not in channel._inviteList, return */
                                if (channelPtr->getMode().find('i') != std::string::npos && !channelPtr->isInvited(&user)) {
                                    std::string message = std::string(ERR_INVITEONLYCHAN) + " " + user.getNickname() + " " + channelsToJoin[i] + " :Cannot join channel (+i)\r\n";
                                    TCPserver::sendReply(user, message);
                                    user.deleteCommand("JOIN");
                                    return;
                                }
                                /* if channel no key                  OR       if channel has key        and user has key     and               keys match */
                                if ((channelPtr->getKey().size() == 0) || ((channelPtr->getKey().size() > 0 && keys.size() > 0) && (channelPtr->getKey() == keys[i]))) {
                                    if (!channelPtr->getLimit() || channelPtr->getLimit() > channelPtr->getUsers().size()) {
                                        channelPtr->addUser(&user);
                                        user.addChannel(channelPtr);
                                        std::string reply = ":" + user.getFullname() + " JOIN :" + channelsToJoin[i] + "\r\n";
                                        TCPserver::sendReply(user, reply);
                                        TCPserver::broadcastMessage(reply, channelPtr->getUsers(), user);
                                        reply = std::string(RPL_TOPIC) + " " + user.getNickname() + " " + channelsToJoin[i] + " :" + channelPtr->getTopic() + "\r\n";
                                        TCPserver::sendReply(user, reply);
                                        reply = std::string(RPL_NAMREPLY) + " " + user.getNickname() + " = " + channelsToJoin[i] + " :" + channelPtr->getUsersNames() + "\r\n";
                                        TCPserver::sendReply(user, reply);
                                        reply = std::string(RPL_ENDOFNAMES) + " " + user.getNickname() + " " + channelsToJoin[i] + " :End of /NAMES list\r\n";
                                        TCPserver::sendReply(user, reply);
                                        reply = std::string(RPL_CREATIONTIME) + " " + user.getNickname() + " " + channelsToJoin[i] + " " + toString(channelPtr->getCreationTime()) + "\r\n";
                                        TCPserver::sendReply(user, reply);
                                    } else {
                                        std::string message = std::string(ERR_CHANNELISFULL) + " " + channelPtr->getName() + " " + channelsToJoin[i] + " :Cannot join channel (+l)\r\n";
                                        TCPserver::sendReply(user, message);
                                    }
                                } else {
                                    std::string message = std::string(ERR_BADCHANNELKEY) + " " + user.getNickname() + " " + channelsToJoin[i] + " :Cannot join channel (+k)\r\n";
                                    TCPserver::sendReply(user, message);
                                }
                            } else {
                                std::string message = std::string(ERR_BANNEDFROMCHAN) + " " + user.getNickname() + " " + channelsToJoin[i] + " :You are banned from this channel\r\n";
                                TCPserver::sendReply(user, message);
                            }
                        } else {
                            std::string message = std::string(ERR_USERONCHANNEL) + " " + user.getNickname() + " " + channelsToJoin[i] + " :is already on channel\r\n";
                            TCPserver::sendReply(user, message);
                        }
                    } else {
                        Channel* newChannel = new Channel(channelsToJoin[i]);
                        newChannel->addUser(&user);
                        newChannel->addOperator(&user);
                        user.addChannel(newChannel);
                        TCPserver::getChannels().push_back(newChannel);
                        std::string reply = ":" + user.getFullname() + " JOIN :" + channelsToJoin[i] + "\r\n";
                        TCPserver::sendReply(user, reply);
                        reply = std::string(RPL_TOPIC) + " " + user.getNickname() + " " + channelsToJoin[i] + " :" + newChannel->getTopic() + "\r\n";
                        TCPserver::sendReply(user, reply);
                        reply = std::string(RPL_NAMREPLY) + " " + user.getNickname() + " = " + channelsToJoin[i] + " :" + newChannel->getUsersNames() + "\r\n";
                        TCPserver::sendReply(user, reply);
                        reply = std::string(RPL_ENDOFNAMES) + " " + user.getNickname() + " " + channelsToJoin[i] + " :End of /NAMES list\r\n";
                        TCPserver::sendReply(user, reply);
                        reply = std::string(RPL_CREATIONTIME) + " " + user.getNickname() + " " + channelsToJoin[i] + " " + toString(newChannel->getCreationTime()) + "\r\n";
                        TCPserver::sendReply(user, reply);
                    }
                } else {
                    std::string message = std::string(ERR_NOSUCHCHANNEL) + " " + user.getNickname() + " " + channelsToJoin[i] + " :No such channel\r\n";
                    TCPserver::sendReply(user, message);
                }
            }
        }
    }
    user.deleteCommand("JOIN");
}

/**
 * TOPIC command:
 *
 * @param user The user who sent the command.
 * @param command the command that was sent to the server
 */
void handleTOPIC(User& user, std::vector<std::string> const& command) {
    if (command.size() > 1) {
        std::string channel_name = command[1];
        if (channel_name.size() > 0) {
            if (TCPserver::isChannelNameTaken(channel_name)) {
                Channel* channelRef = TCPserver::getChannel(channel_name);
                if (channelRef->isUserInChannel(user)) {
                    if (command.size() > 2) {
                        if (channelRef->isChannelOperator(&user) || channelRef->getMode().find('t') == std::string::npos) {
                            std::string topic = "";
                            for (std::string::size_type i(2); i < command.size(); i++) {
                                topic += command[i] + " ";
                            }
                            if (topic[0] == ':') {
                                topic = topic.substr(1);
                            }
                            channelRef->setTopicCreationTime(time(NULL));
                            channelRef->setTopic(topic);
                            std::string reply = ":" + user.getFullname() + " TOPIC " + channel_name + " :" + channelRef->getTopic() + "\r\n";
                            TCPserver::sendReply(user, reply);
                            TCPserver::broadcastMessage(reply, channelRef->getUsers(), user);
                            std::cout << displayTimestamp() << "-!- [CHANNEL " << channel_name << "] " << user.getFullname() << " changed the topic to: " << channelRef->getTopic() << std::endl;
                        } else {
                            std::string message = std::string(ERR_CHANOPRIVSNEEDED) + " " + channel_name + " :You're not channel operator\r\n";
                            TCPserver::sendReply(user, message);
                        }
                    } else {
                        if (channelRef->getTopic().size() > 0) {
                            std::string reply = std::string(RPL_TOPIC) + " " + user.getNickname() + " " + channel_name + " :" + channelRef->getTopic() + "\r\n";
                            TCPserver::sendReply(user, reply);
                            reply = std::string(RPL_TOPICWHOTIME) + " " + user.getNickname() + " " + channel_name + " " + user.getFullname() + " " + toString(channelRef->getCreationTime()) + "\r\n";
                            TCPserver::sendReply(user, reply);
                        } else {
                            std::string reply = std::string(RPL_NOTOPIC) + " " + user.getNickname() + " " + channel_name + " :No topic is set\r\n";
                            TCPserver::sendReply(user, reply);
                        }
                    }
                } else {
                    std::string message = std::string(ERR_NOTONCHANNEL) + " " + user.getNickname() + " " + channel_name + " :You're not on that channel\r\n";
                    TCPserver::sendReply(user, message);
                }
            } else {
                std::string message = std::string(ERR_NOSUCHCHANNEL) + " " + channel_name + " :No such channel\r\n";
                TCPserver::sendReply(user, message);
            }
        } else {
            std::string message = std::string(ERR_NEEDMOREPARAMS) + " :Not enough parameters\r\n";
            TCPserver::sendReply(user, message);
        }
    } else {
        std::string message = std::string(ERR_NEEDMOREPARAMS) + " :Not enough parameters\r\n";
        TCPserver::sendReply(user, message);
    }
    user.deleteCommand("TOPIC");
}

/**
 * This function is used to send a private message to another user.
 *
 * @param user The user who sent the command
 * @param command vector of strings, where each string is a word in the command
 */
void privatePRIVMSG(User& user, std::vector<std::string> const& command) {
    std::map<int, User>::iterator it;
    for (it = TCPserver::getUsers().begin(); it != TCPserver::getUsers().end(); it++) {
        if (it->second.getNickname() == command[1]) {
            std::string message = "";
            for (std::string::size_type i(2); i < command.size(); i++) {
                message += command[i] + " ";
            }
            std::string reply = ":" + user.getFullname() + " PRIVMSG " + it->second.getNickname() + " " + message + "\r\n";
            TCPserver::sendReply(it->second, reply);
            user.deleteCommand("PRIVMSG");
            return;
        }
    }
    std::string message = std::string(ERR_NOSUCHNICK) + " " + command[1] + " : No such nick/channel\r\n";
    TCPserver::sendReply(user, message);
    user.deleteCommand("PRIVMSG");
}

/**
 * PRIVMSG command:
 *
 * https://modern.ircdocs.horse/#privmsg-message
 *
 * @param user The user who sent the message
 * @param command the command that was sent by the user
 */
void handlePRIVMSG(User& user, std::vector<std::string> const& command) {
    if (command.size() > 2) {
        if (command[1][0] != '#') {
            privatePRIVMSG(user, command);
            return;
        }
        std::string channel_name = command[1];
        if (channel_name.size() > 0) {
            if (TCPserver::isChannelNameTaken(channel_name)) {
                Channel* channelPtr = TCPserver::getChannel(channel_name);
                if (((channelPtr->getMode().find('n') == std::string::npos) || (((channelPtr->getMode().find('n') != std::string::npos) && channelPtr->isUserInChannel(user)))) // gere le mode +n
                    && !channelPtr->isBanned(user.getFullname())
                    && (channelPtr->getMode().find('m') == std::string::npos || (channelPtr->isChannelOperator(&user) || channelPtr->isVoiced(&user)))) { // gere le mode +m
                    std::string message = "";
                    for (std::string::size_type i(2); i < command.size(); i++) {
                        message += command[i] + " ";
                    }
                    std::string reply = ":" + user.getFullname() + " PRIVMSG " + channel_name + " " + message + "\r\n";
                    TCPserver::broadcastMessage(reply, channelPtr->getUsers(), user);
                } else {
                    std::string message = std::string(ERR_CANNOTSENDTOCHAN) + " " + channel_name + " :Cannot send to channel\r\n";
                    TCPserver::sendReply(user, message);
                }
            } else {
                std::string message = std::string(ERR_NOSUCHCHANNEL) + " " + channel_name + " :No such channel\r\n";
                TCPserver::sendReply(user, message);
            }
        } else {
            std::string message = std::string(ERR_NEEDMOREPARAMS) + " :Not enough parameters\r\n";
            TCPserver::sendReply(user, message);
        }
    } else {
        std::string message = std::string(ERR_NEEDMOREPARAMS) + " :Not enough parameters\r\n";
        TCPserver::sendReply(user, message);
    }
    user.deleteCommand("PRIVMSG");
}

void privateNOTICE(User& user, std::vector<std::string> const& command) {
    std::map<int, User>::iterator it;
    for (it = TCPserver::getUsers().begin(); it != TCPserver::getUsers().end(); it++) {
        if (it->second.getNickname() == command[1]) {
            std::string message = "";
            for (std::string::size_type i(2); i < command.size(); i++) {
                message += command[i] + " ";
            }
            std::string reply = ":" + user.getFullname() + " NOTICE " + it->second.getNickname() + " " + message + "\r\n";
            TCPserver::sendReply(it->second, reply);
            user.deleteCommand("NOTICE");
            return;
        }
    }
    std::string message = std::string(ERR_NOSUCHNICK) + " " + command[1] + " : No such nick/channel\r\n";
    TCPserver::sendReply(user, message);
    user.deleteCommand("NOTICE");
}

void handleNOTICE(User& user, std::vector<std::string> const& command) {
    if (command.size() > 2) {
        if (command[1][0] != '#') {
            privateNOTICE(user, command);
            return;
        }
        std::string channel_name = command[1];
        if (channel_name.size() > 0) {
            if (TCPserver::isChannelNameTaken(channel_name)) {
                Channel* channelPtr = TCPserver::getChannel(channel_name);
                if (((channelPtr->getMode().find('n') == std::string::npos) || (((channelPtr->getMode().find('n') != std::string::npos) && channelPtr->isUserInChannel(user)))) // gere le mode +n
                    && !channelPtr->isBanned(user.getFullname())
                    && (channelPtr->getMode().find('m') == std::string::npos || (channelPtr->isChannelOperator(&user) || channelPtr->isVoiced(&user)))) { // gere le mode +m
                    std::string message = "";
                    for (std::string::size_type i(2); i < command.size(); i++) {
                        message += command[i] + " ";
                    }
                    std::string reply = ":" + user.getFullname() + " NOTICE " + channel_name + " " + message + "\r\n";
                    TCPserver::broadcastMessage(reply, channelPtr->getUsers(), user);
                } else {
                    std::string message = std::string(ERR_CANNOTSENDTOCHAN) + " " + channel_name + " :Cannot send to channel\r\n";
                    TCPserver::sendReply(user, message);
                }
            } else {
                std::string message = std::string(ERR_NOSUCHCHANNEL) + " " + channel_name + " :No such channel\r\n";
                TCPserver::sendReply(user, message);
            }
        } else {
            std::string message = std::string(ERR_NEEDMOREPARAMS) + " :Not enough parameters\r\n";
            TCPserver::sendReply(user, message);
        }
    } else {
        std::string message = std::string(ERR_NEEDMOREPARAMS) + " :Not enough parameters\r\n";
        TCPserver::sendReply(user, message);
    }
    user.deleteCommand("NOTICE");
}

/**
 * PART command:
 *
 * https://modern.ircdocs.horse/#part-message
 *
 * @param user The user who sent the command
 * @param command a vector of strings, where each string is a word in the command.
 */
void handlePART(User& user, std::vector<std::string> const& command) {
    if (command.size() > 1) {
        std::string channel_name = command[1];
        if (channel_name.size() > 0) {
            /* split command in case several channel names has been entered */
            std::vector<std::string> channelsToPart = split(channel_name, ",");
            for (std::vector<std::string>::iterator it = channelsToPart.begin(); it != channelsToPart.end(); ++it) {
                if (TCPserver::isChannelNameTaken(*it)) {
                    Channel* channelPtr = TCPserver::getChannel(*it);
                    if (channelPtr->isUserInChannel(user)) {
                        std::string reply = ":" + user.getFullname() + " PART " + *it;
                        if (command.size() > 2) {
                            std::string message = "";
                            for (std::string::size_type i(2); i < command.size(); i++) {
                                if (i == 2)
                                    message += command[i][0] == ':' ? command[i].substr(1, command[i].size()) + " " : command[i] + " ";
                                else if (i == command.size() - 1)
                                    message += command[i];
                                else
                                    message += command[i] + " ";
                            }
                            reply += " :" + message + "\r\n";
                        } else {
                            reply += "\r\n";
                        }
                        TCPserver::sendReply(user, reply);
                        TCPserver::broadcastMessage(reply, channelPtr->getUsers(), user);
                        channelPtr->removeUser(&user);
                        if (channelPtr->getUsers().size() == 0) {
                            TCPserver::removeChannel(*it);
                        }
                    } else {
                        std::string message = std::string(ERR_NOTONCHANNEL) + " " + *it + " :You're not on that channel\r\n";
                        TCPserver::sendReply(user, message);
                    }
                } else {
                    std::string message = std::string(ERR_NOSUCHCHANNEL) + " " + *it + " :No such channel\r\n";
                    TCPserver::sendReply(user, message);
                }
            }
        } else {
            std::string message = std::string(ERR_NEEDMOREPARAMS) + " :Not enough parameters\r\n";
            TCPserver::sendReply(user, message);
        }
    } else {
        std::string message = std::string(ERR_NEEDMOREPARAMS) + " :Not enough parameters\r\n";
        TCPserver::sendReply(user, message);
    }
    user.deleteCommand("PART");
}

void handleWHO(User* user, std::vector<std::string> const& command) {
    if (command.size() > 1) {
        std::string target = command[1];
        if (target.size() > 0 && target[0] == '#') {
            if (TCPserver::isChannelNameTaken(target)) {
                Channel* channelPtr = TCPserver::getChannel(target);
                std::map<int, User*> users = channelPtr->getUsers();
                for (std::map<int, User*>::iterator it = users.begin(); it != users.end(); it++) {
                    if (it->second->getMode().find('i') == std::string::npos) {
                        std::string reply = ":" + std::string(SERVER_NAME) + " " + RPL_WHOREPLY + " " + user->getNickname() + " " + channelPtr->getName() + " ~" + it->second->getUsername() + " " + it->second->getHostname() + " " + SERVER_NAME + " " + it->second->getNickname() + " H :0 " + it->second->getRealName() + "\r\n";
                        TCPserver::sendReply(*user, reply);
                    }
                }
                std::string reply = ":" + std::string(SERVER_NAME) + " " + RPL_ENDOFWHO + " " + user->getNickname() + " " + target + " :End of /WHO list\r\n";
                TCPserver::sendReply(*user, reply);
            } else {
                std::string message = std::string(ERR_NOSUCHCHANNEL) + " " + target + " :No such channel\r\n";
                TCPserver::sendReply(*user, message);
            }
        } else {
            if (isNicknameTaken(target, TCPserver::getUsers())) {
                User& targetRef = TCPserver::getUser(target);
                if (targetRef.getMode().find('i') != std::string::npos) {
                    std::string message = std::string(ERR_USERSDONTMATCH) + " : Cannot send to a user who is invisible\r\n";
                    TCPserver::sendReply(*user, message);
                } else {
                    std::string reply = ":" + std::string(SERVER_NAME) + " " + RPL_WHOREPLY + " " + targetRef.getNickname() + " " + SERVER_NAME + " ~" + targetRef.getUsername() + " " + targetRef.getHostname() + " " + SERVER_NAME + " " + targetRef.getNickname() + " H :0 " + targetRef.getRealName() + "\r\n";
                    TCPserver::sendReply(*user, reply);
                    std::string reply2 = ":" + std::string(SERVER_NAME) + " " + RPL_ENDOFWHO + " " + user->getNickname() + " " + target + " :End of /WHO list\r\n";
                    TCPserver::sendReply(*user, reply2);
                }
            } else {
                std::string message = std::string(ERR_NOSUCHNICK) + " " + target + " :No such nick\r\n";
                TCPserver::sendReply(*user, message);
            }
        }
    } else {
        std::string message = std::string(ERR_NEEDMOREPARAMS) + " :Not enough parameters\r\n";
        TCPserver::sendReply(*user, message);
    }
    user->deleteCommand("WHO");
}

void handleINVITE(User& user, std::vector<std::string> const& command) {
    if (command.size() > 2) {
        std::string nickName = command[1];
        std::string channelName = command[2];
        if (nickName.size() > 0 && channelName.size() > 0) {
            if (TCPserver::isChannelNameTaken(channelName)) {
                Channel* channelPtr = TCPserver::getChannel(channelName);
                if (channelPtr->isUserInChannel(user)) {
                    if (channelPtr->isChannelOperator(&user)) {
                        if (isNicknameTaken(nickName, TCPserver::getUsers())) {
                            User& targetRef = TCPserver::getUser(nickName);
                            if (!channelPtr->isUserInChannel(targetRef)) {
                                std::cout << displayTimestamp() << "-!- [CHANNEL " << channelPtr->getName() << "] " << user.getNickname() << " invited " << targetRef.getNickname() << std::endl;
                                channelPtr->addToInvitList(&targetRef);
                                std::string message = ":" + user.getFullname() + " INVITE " + nickName + " " + channelName + "\r\n";
                                TCPserver::sendReply(targetRef, message);
                            } else {
                                std::string message = std::string(ERR_USERONCHANNEL) + " " + nickName + " " + nickName + " " + channelName + " :is already on channel\r\n";
                                TCPserver::sendReply(user, message);
                            }
                        } else {
                            std::string message = std::string(ERR_NOSUCHNICK) + " " + nickName + " :No such nick/channel\r\n";
                            TCPserver::sendReply(user, message);
                        }
                    } else {
                        std::string message = std::string(ERR_CHANOPRIVSNEEDED) + " " + channelName + " :You're not channel operator\r\n";
                        TCPserver::sendReply(user, message);
                    }
                } else {
                    std::string message = std::string(ERR_NOTONCHANNEL) + " " + channelName + " :You're not on that channel\r\n";
                    TCPserver::sendReply(user, message);
                }
            } else {
                std::string message = std::string(ERR_NOSUCHCHANNEL) + " " + channelName + " :No such channel\r\n";
                TCPserver::sendReply(user, message);
            }
        } else {
            std::string message = std::string(ERR_NEEDMOREPARAMS) + " INVITE :Not enough parameters\r\n";
            TCPserver::sendReply(user, message);
        }
    } else {
        std::string message = std::string(ERR_NEEDMOREPARAMS) + " :Not enough parameters\r\n";
        TCPserver::sendReply(user, message);
    }
    user.deleteCommand("INVITE");
}

void handleKICK(User& user, std::vector<std::string> const& command) {
    if (command.size() > 2) {
        std::string channel_name = command[1];
        if (channel_name.size() > 0) {
            if (TCPserver::isChannelNameTaken(channel_name)) {
                Channel* channelPtr = TCPserver::getChannel(channel_name);
                if (channelPtr->isUserInChannel(user)) {
                    if (channelPtr->isChannelOperator(&user)) {
                        std::string target = command[2];
                        if (target.size() > 0) {
                            if (target != user.getNickname()) {
                                std::map<int, User> usersToCheck;
                                std::map<int, User*> usersRef = channelPtr->getUsers();
                                for (std::map<int, User*>::iterator it = usersRef.begin(); it != usersRef.end(); it++) {
                                    usersToCheck[it->first] = *it->second;
                                }
                                if (isNicknameTaken(target, usersToCheck)) {
                                    User& targetRef = channelPtr->getUserByNickname(target);
                                    if (channelPtr->isUserInChannel(targetRef)) {
                                        std::string reply = ":" + user.getFullname() + " KICK " + channel_name + " " + target + " ";
                                        if (command.size() > 3) {
                                            std::string message = "";
                                            for (std::string::size_type i(3); i < command.size(); i++) {
                                                if (i == 3)
                                                    message += command[i][0] == ':' ? command[i].substr(1, command[i].size()) + " " : command[i] + " ";
                                                else if (i == command.size() - 1)
                                                    message += command[i];
                                                else
                                                    message += command[i] + " ";
                                            }
                                            reply += ":" + message + "\r\n";
                                        } else {
                                            reply += ":" + target + " was kicked from " + channel_name + "\r\n";
                                        }
                                        TCPserver::sendReply(user, reply);
                                        TCPserver::broadcastMessage(reply, channelPtr->getUsers(), user);
                                        channelPtr->removeUser(&targetRef);
                                        if (channelPtr->getUsers().size() == 0) {
                                            TCPserver::removeChannel(channel_name);
                                        }
                                    } else {
                                        std::string message = std::string(ERR_USERNOTINCHANNEL) + " " + target + " " + channel_name + " :Not on that channel\r\n";
                                        TCPserver::sendReply(user, message);
                                    }
                                } else {
                                    std::string message = std::string(ERR_NOSUCHNICK) + " " + target + " :No such nick/channel\r\n";
                                    TCPserver::sendReply(user, message);
                                }
                            } else {
                                std::string message = user.getNickname() + " " + channel_name + " :Cannot kick yourself\r\n";
                                TCPserver::sendReply(user, message);
                            }
                        } else {
                            std::string message = std::string(ERR_NEEDMOREPARAMS) + " KICK " + channel_name + " :Not enough parameters\r\n";
                            TCPserver::sendReply(user, message);
                        }
                    } else {
                        std::string message = std::string(ERR_CHANOPRIVSNEEDED) + " " + channel_name + " :You're not channel operator\r\n";
                        TCPserver::sendReply(user, message);
                    }
                } else {
                    std::string message = std::string(ERR_NOTONCHANNEL) + " " + channel_name + " :You're not on that channel\r\n";
                    TCPserver::sendReply(user, message);
                }
            } else {
                std::string message = std::string(ERR_NOSUCHCHANNEL) + " " + channel_name + " :No such channel\r\n";
                TCPserver::sendReply(user, message);
            }
        } else {
            std::string message = std::string(ERR_NEEDMOREPARAMS) + " KICK :Not enough parameters\r\n";
            TCPserver::sendReply(user, message);
        }
    } else {
        std::string message = std::string(ERR_NEEDMOREPARAMS) + " :Not enough parameters\r\n";
        TCPserver::sendReply(user, message);
    }
    user.deleteCommand("KICK");
}

// void handleNAMES(User& user)
/**
 * MOTD command:
 *
 * https://modern.ircdocs.horse/#motd-message
 *
 * @param user The user who sent the command.
 * @param command The command that was sent by the user.
 */
void handleMOTD(User& user) {
    std::string message = std::string(RPL_MOTDSTART) + " :- " + SERVER_NAME + " Message of the day - \r\n";
    TCPserver::sendReply(user, message);
    std::ifstream file("motd/motd.txt");
    if (file.is_open()) {
        std::string line;
        while (getline(file, line)) {
            message = std::string(RPL_MOTD) + " :- " + line + "\r\n";
            TCPserver::sendReply(user, message);
        }
        file.close();
    }
    message = std::string(RPL_ENDOFMOTD) + " : End of MOTD command\r\n";
    TCPserver::sendReply(user, message);
    user.deleteCommand("MOTD");
    user.deleteCommand("motd");
}

void handleLUSERS(User& user) {
    int invisibleUsers(0);
    for (std::map<int, User>::iterator it = TCPserver::getUsers().begin(); it != TCPserver::getUsers().end(); it++) {
        if (it->second.getMode().find('i') != std::string::npos) {
            invisibleUsers++;
        }
    }
    std::string message = std::string(RPL_LUSERCLIENT) + " : There are " + toString(TCPserver::getUsers().size()) + " user(s) and " + toString(invisibleUsers) + " invisible on 1 server\r\n";
    TCPserver::sendReply(user, message);

    int operators(0);
    for (std::map<int, User>::iterator it = TCPserver::getUsers().begin(); it != TCPserver::getUsers().end(); it++) {
        if (it->second.getMode().find('o') != std::string::npos) {
            operators++;
        }
    }
    message = std::string(RPL_LUSEROP) + " : " + toString(operators) + " :operator(s) online\r\n";
    TCPserver::sendReply(user, message);

    message = std::string(RPL_LUSERCHANNELS) + " : " + toString(TCPserver::getChannels().size()) + " :channel(s) formed\r\n";
    TCPserver::sendReply(user, message);
    message = std::string(RPL_LUSERME) + " : I have " + toString(TCPserver::getUsers().size()) + " client(s) and " + toString(TCPserver::getChannels().size()) + " channel(s) and 1 server\r\n";
    TCPserver::sendReply(user, message);
    user.deleteCommand("lusers");
}

/**
 * LIST command.
 *
 * @param user The user who sent the command.
 */
void handleLIST(User& user) {
    std::stringstream ss;
    std::string message;

    ss << std::left << std::setw(10) << "Channel" << std::setw(10) << "Users" << std::setw(10) << "Topic" << std::endl;
    message = ":" + std::string(RPL_LIST) + " " + ss.str() + "\r\n";
    TCPserver::sendReply(user, message);

    for (std::vector<Channel*>::iterator it = TCPserver::getChannels().begin(); it != TCPserver::getChannels().end(); it++) {
        ss.str(std::string());
        ss << std::left << std::setw(10) << (*it)->getName() << std::setw(10) << (*it)->getUsers().size() << std::setw(10) << (*it)->getTopic() << std::endl;
        message = ":" + std::string(RPL_LIST) + " " + ss.str() + "\r\n";
        if ((*it)->getMode().find('p') == std::string::npos && (*it)->getMode().find('s') == std::string::npos)
            TCPserver::sendReply(user, message);
    }
    message = ":" + std::string(RPL_LISTEND) + " :End of LIST\r\n";
    TCPserver::sendReply(user, message);
    user.deleteCommand("LIST");
}

void handleKILL(User& user, std::vector<std::string> const& command) {
    if (command.size() > 1) {
        std::string target = command[1];
        if (command.size() > 2) {
            std::string reason;
            if (command.size() > 3) {
                for (std::string::size_type i(2); i < command.size(); i++) {
                    if (i != command.size() - 1) {
                        reason += command[i] + " ";
                    } else {
                        reason += command[i];
                    }
                }
            } else {
                reason = command[2] + "no reason";
            }
            if (user.getMode().find('o') != std::string::npos) {
                if (target != user.getNickname()) {
                    if (isNicknameTaken(target, TCPserver::getUsers())) {
                        std::string message = ":" + user.getFullname() + " KILL :" + target + " :Killed (" + user.getNickname() + " (" + reason + "))\r\n";
                        TCPserver::sendReply(TCPserver::getUser(target), message);
                        message = ":" + TCPserver::getUser(target).getFullname() + " QUIT :" + target + " :Killed (" + user.getNickname() + " (" + reason + "))\r\n";
                        TCPserver::sendReply(TCPserver::getUser(target), message);
                        for (std::vector<Channel*>::iterator it = TCPserver::getChannels().begin(); it != TCPserver::getChannels().end(); it++) {
                            for (std::map<int, User>::iterator it2 = TCPserver::getUsers().begin(); it2 != TCPserver::getUsers().end(); it2++) {
                                if ((*it)->isUserInChannel(it2->second)) {
                                    TCPserver::sendReply(it2->second, message);
                                }
                            }
                        }
                        TCPserver::getUser(target).setKill(TRUE);
                        std::string ping = "PING " + TCPserver::getUsers().begin()->second.getFullname() + "\r\n";
                        TCPserver::sendReply(TCPserver::getUser(target), ping);
                    } else {
                        std::string message = ":" + std::string(ERR_NOSUCHNICK) + " " + target + " No such nick/channel\r\n";
                        TCPserver::sendReply(user, message);
                    }
                } else {
                    std::string message = ":" + std::string(ERR_CANTKILLSERVER) + " You can't kill yourself\r\n";
                    TCPserver::sendReply(user, message);
                }
            } else {
                std::string message = ":" + std::string(ERR_NOPRIVILEGES) + " Permission Denied: You're not an IRC operator\r\n";
                TCPserver::sendReply(user, message);
            }
        } else {
            std::string message = ":" + std::string(ERR_NEEDMOREPARAMS) + " KILL " + target + " Not enough parameters\r\n";
            TCPserver::sendReply(user, message);
        }
    } else {
        std::string message = ":" + std::string(ERR_NEEDMOREPARAMS) + " KILL Not enough parameters\r\n";
        TCPserver::sendReply(user, message);
    }
    user.deleteCommand("kill");
}

void handleOPER(User& user, std::vector<std::string> const& command) {
    if (command.size() > 2) {
        std::string nickname = command[1];
        std::string password = command[2];
        std::string host = user.getHostname();
        std::string message;
        for (std::vector<ServerOperator>::iterator it = TCPserver::getServerOperators().begin(); it != TCPserver::getServerOperators().end(); it++) {
            if (it->getNickname() == nickname) {
                if (it->getPassword() == password) {
                    if (it->getHost() == host) {
                        user.setMode('o', TRUE);
                        user.setServerOperator(TRUE);
                        message = ":" + std::string(RPL_YOUREOPER) + " You are now an IRC operator\r\n";
                        TCPserver::sendReply(user, message);
                        message = std::string(RPL_UMODEIS) + " " + user.getNickname() + " " + user.getMode() + "\r\n";
                        TCPserver::sendReply(user, message);
                        user.deleteCommand("OPER");
                        return;
                    } else {
                        message = ":" + std::string(ERR_NOOPERHOST) + " No O-lines for your host\r\n";
                        TCPserver::sendReply(user, message);
                        user.deleteCommand("OPER");
                        return;
                    }
                } else {
                    message = ":" + std::string(ERR_PASSWDMISMATCH) + " Password incorrect\r\n";
                    TCPserver::sendReply(user, message);
                    user.deleteCommand("OPER");
                    return;
                }
            } else {
                message = ":" + std::string(ERR_NOOPERHOST) + " No O-lines for your host\r\n";
                TCPserver::sendReply(user, message);
                user.deleteCommand("OPER");
                return;
            }
        }
    } else {
        std::string message = ":" + std::string(ERR_NEEDMOREPARAMS) + " OPER Not enough parameters\r\n";
        TCPserver::sendReply(user, message);
    }
    user.deleteCommand("OPER");
}

void handleWALLOPS(User& user, std::vector<std::string> const& command) {
    if (user.getMode().find('o') != std::string::npos) {
        if (command.size() > 1) {
            std::string message;
            for (std::string::size_type i(1); i < command.size(); i++) {
                if (i != command.size() - 1) {
                    message += command[i] + " ";
                } else {
                    message += command[i];
                }
            }
            message = ":" + user.getFullname() + " WALLOPS " + message + "\r\n";
            for (std::map<int, User>::iterator it = TCPserver::getUsers().begin(); it != TCPserver::getUsers().end(); it++) {
                if (it->second.getMode().find('w') != std::string::npos) {
                    TCPserver::sendReply(it->second, message);
                }
            }
        } else {
            std::string message = ":" + std::string(ERR_NEEDMOREPARAMS) + " WALLOPS Not enough parameters\r\n";
            TCPserver::sendReply(user, message);
        }
    } else {
        std::string message = ":" + std::string(ERR_NOPRIVILEGES) + " Permission Denied: You're not an IRC operator\r\n";
        TCPserver::sendReply(user, message);
    }
    user.deleteCommand("wallops");
}

void handleRESTART(User& user) {
    if (user.getMode().find('o') != std::string::npos) {
        std::string message = ":" + std::string(SERVER_NAME) + " Server restarting\r\n";
        for (std::map<int, User>::iterator it = TCPserver::getUsers().begin(); it != TCPserver::getUsers().end(); it++) {
            TCPserver::sendReply(it->second, message);
        }
        for (std::map<int, User>::iterator it = TCPserver::getUsers().begin(); it != TCPserver::getUsers().end(); ++it) {
            close(it->first);
        }
        close(TCPserver::getSocket().getFD());
        TCPserver::getUsers().clear();
        TCPserver::getChannels().clear();
        TCPserver::getpfds().clear();
        TCPserver::setRestart(TRUE);
    } else {
        std::string message = ":" + std::string(ERR_NOPRIVILEGES) + " Permission Denied: You're not an IRC operator\r\n";
        TCPserver::sendReply(user, message);
        user.deleteCommand("restart");
    }
}

/**
 * Changes the nickname of the user:
 *
 * https://modern.ircdocs.horse/#nick-message
 *
 * @param user The user who is changing their nickname
 * @param nickname the new nickname
 */
void changeNICK(User* user, std::string const& nickname) {
    if (nickname.size() > 0) {
        std::cout << displayTimestamp() << "[" << user->getFD() << "] [SERVER] Requested nickname: [" << nickname << "]" << std::endl;
        if (isNicknameValid(nickname) && nickname != SERVER_NAME) {
            /* check if nickname is already taken in the server's _user map */
            if (isNicknameTaken(nickname, TCPserver::getUsers())) {
                std::string message = ":" + user->getFullname() + " " + std::string(ERR_NICKNAMEINUSE) + " " + nickname + " " + nickname + " :Nickname is already in use\r\n";
                TCPserver::sendReply(*user, message);
                user->deleteCommand("NICK");
                return;
            }
            /* if nickname is not taken, set it */
            std::string oldnickname = user->getNickname();
            user->setNickname(nickname);
            std::cout << displayTimestamp() << "[" << user->getFD() << "] [SERVER] Nickname set to: [" << nickname << "]" << std::endl;
            std::string message = ":" + oldnickname + "!" + user->getUsername() + "@" + user->getHostname() + " NICK " + user->getNickname() + "\r\n";
            TCPserver::sendReply(*user, message);
            for (std::vector<Channel*>::iterator it = TCPserver::getChannels().begin(); it != TCPserver::getChannels().end(); ++it) {
                if ((*it)->isUserInChannel(*user)) {
                    TCPserver::broadcastMessage(message, (*it)->getUsers(), *user);
                }
            }
            user->deleteCommand("NICK");
        } else {
            /* if nickname is not valid, send error message */
            std::string message = std::string(ERR_ERRONEUSNICKNAME) + " " + nickname + " :Erroneous nickname\r\n";
            TCPserver::sendReply(*user, message);
            user->setAuthenticated(FALSE);
        }
    } else {
        /* if nickname is empty, send error message */
        std::string message = std::string(ERR_NONICKNAMEGIVEN) + " :No nickname given\r\n";
        TCPserver::sendReply(*user, message);
        user->setAuthenticated(FALSE);
    }
}

/**
 * Handles the commands sent by the client.
 *
 * @param user The user object that is connected to the client.
 */
void handleClientCommands(User* user) {
    std::vector<std::vector<std::string> > commands = user->getCommands();
    for (std::vector<std::vector<std::string> >::size_type i(0); i < commands.size(); i++) {
        if (commands[i].size() > 0) {
            if (commands[i][0] == "WHOIS") {
                handleWHOIS(*user, commands[i]);
            } else if (commands[i][0] == "PING") {
                handlePING(*user, commands[i]);
            } else if (commands[i][0] == "MODE") {
                handleMODE(user, commands[i]);
            } else if (commands[i][0] == "QUIT") {
                handleQUIT(*user, commands[i]);
            } else if (commands[i][0] == "JOIN") {
                handleJOIN(*user, commands[i]);
            } else if (commands[i][0] == "TOPIC") {
                handleTOPIC(*user, commands[i]);
            } else if (commands[i][0] == "PRIVMSG") {
                handlePRIVMSG(*user, commands[i]);
            } else if (commands[i][0] == "PART") {
                handlePART(*user, commands[i]);
            } else if (commands[i][0] == "WHO") {
                handleWHO(user, commands[i]);
            } else if (commands[i][0] == "motd") {
                handleMOTD(*user);
            } else if (commands[i][0] == "lusers") {
                handleLUSERS(*user);
            } else if (commands[i][0] == "NICK" && user->isRegistered()) {
                changeNICK(user, commands[i][1]);
            } else if (commands[i][0] == "KICK") {
                handleKICK(*user, commands[i]);
            } else if (commands[i][0] == "INVITE") {
                handleINVITE(*user, commands[i]);
            } else if (commands[i][0] == "LIST") {
                handleLIST(*user);
            } else if (commands[i][0] == "kill") {
                handleKILL(*user, commands[i]);
            } else if (commands[i][0] == "PONG") {
                user->deleteCommand("PONG");
            } else if (commands[i][0] == "OPER") {
                handleOPER(*user, commands[i]);
            } else if (commands[i][0] == "wallops") {
                handleWALLOPS(*user, commands[i]);
            } else if (commands[i][0] == "restart") {
                handleRESTART(*user);
            } else if (commands[i][0] == "NOTICE") {
                handleNOTICE(*user, commands[i]);
            } else {
                std::string message = std::string(ERR_UNKNOWNCOMMAND) + " " + commands[i][0] + " :Unknown command\r\n";
                TCPserver::sendReply(*user, message);
                user->deleteCommand(commands[i][0]);
            }
        }
    }
}