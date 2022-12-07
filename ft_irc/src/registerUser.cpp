#include "../inc/registerUser.hpp"

/**
 * CAP command:
 * https://modern.ircdocs.horse/#cap-message
 *
 * @param user The user who sent the command.
 * @param command The command that was sent to the server.
 */
void handleCAP(User& user, std::vector<std::string> const& command) {
    if (command.size() > 1) {
        user.deleteCommand("CAP");
        /* as CAP is not handled, we just send a 421 error */
        std::string reply = std::string(ERR_UNKNOWNCOMMAND) + " " + command[0] + " :CAP not supported by server\r\n";
        TCPserver::sendReply(user, reply);
    }
}

/**
 * PASS command:
 * https://modern.ircdocs.horse/#pass-message
 *
 * @param user a reference to the User object that is currently logged in
 * @param password the password the user entered
 */
void handlePASS(User& user, std::string const& password) {
    if (password.size() > 0) {
        if (password == TCPserver::getPassword()) {
            std::cout << displayTimestamp() << "[" << user.getFD() << "] [SERVER] Valid password" << std::endl;
            user.deleteCommand("PASS");
            user.setAuthenticated(TRUE);
        } else {
            std::cout << displayTimestamp() << "[" << user.getFD() << "] [SERVER] Invalid password" << std::endl;
            std::string message = std::string(ERR_PASSWDMISMATCH) + " : ERROR :Invalid Password\r\n";
            TCPserver::sendReply(user, message);
            user.setAuthenticated(FALSE);
        }
    } else {
        std::string message = std::string(ERR_NEEDMOREPARAMS) + " : ERROR :This server is password protected\r\n";
        TCPserver::sendReply(user, message);
        user.setAuthenticated(FALSE);
    }
}

/**
 * NICK command:
 * https://modern.ircdocs.horse/#nick-message
 *
 * @param user The user who sent the command.
 * @param command a vector of strings, where each string is a word in the command.
 */
void handleNICK(User& user, std::string const& nickname) {
    if (nickname.size() > 0) {
        std::cout << displayTimestamp() << "[" << user.getFD() << "] [SERVER] Requested nickname: [" << nickname << "]" << std::endl;
        if (isNicknameValid(nickname) && nickname != SERVER_NAME) {
            /* check if nickname is already taken in the server's _user map */
            std::string nickname_ = nickname;
            while (isNicknameTaken(nickname_, TCPserver::getUsers())) {
                nickname_ += "_";
            }
            /* if nickname is not taken, set it */
            user.setNickname(nickname_);
            std::cout << displayTimestamp() << "[" << user.getFD() << "] [SERVER] Nickname set to: [" << nickname_ << "]" << std::endl;
            user.deleteCommand("NICK");
        } else {
            /* if nickname is not valid, send error message */
            std::string message = std::string(ERR_ERRONEUSNICKNAME) + " " + nickname + " :Erroneous nickname\r\n";
            TCPserver::sendReply(user, message);
            user.setAuthenticated(FALSE);
        }
    } else {
        /* if nickname is empty, send error message */
        std::string message = std::string(ERR_NONICKNAMEGIVEN) + " :No nickname given\r\n";
        TCPserver::sendReply(user, message);
        user.setAuthenticated(FALSE);
    }
}

/**
 * USER command:
 * https://modern.ircdocs.horse/#user-message
 *
 * @param user a reference to the user object that is currently connected to the server
 * @param command a vector of strings, where each string is a word in the command.
 */
void handleUSER(User& user, std::vector<std::string> const& command) {
    if (!user.isRegistered()) {
        if (command.size() > 4) {
            if (command[1].size() > 0) {
                user.setUserName(command[1]);
                std::cout << displayTimestamp() << "[" << user.getFD() << "] [SERVER] Username set to: [" << command[1] << "]" << std::endl;
            } else {
                std::string message = std::string(ERR_NEEDMOREPARAMS) + " :username empty\r\n";
                TCPserver::sendReply(user, message);
                user.setAuthenticated(FALSE);
            }
            if (command[3].size() > 0)
                user.setHostname(command[3]);
            if (command[4].size() > 0) {
                std::string realname = "";
                for (std::string::size_type i(4); i < command.size(); i++) {
                    realname += command[i];
                    if (realname.find(":") != std::string::npos) {
                        realname.erase(realname.find(":", 0), 1);
                    }
                    if (i != command.size() - 1)
                        realname += " ";
                }
                user.setRealName(realname);
                std::cout << displayTimestamp() << "[" << user.getFD() << "] [SERVER] Realname set to: [" << realname << "]" << std::endl;
            } else {
                std::string message = std::string(ERR_NEEDMOREPARAMS) + " :realname empty\r\n";
                TCPserver::sendReply(user, message);
                user.setAuthenticated(FALSE);
            }
        }
    } else {
        std::string message = std::string(ERR_ALREADYREGISTRED) + " :You may not reregister\r\n";
        TCPserver::sendReply(user, message);
    }
    user.deleteCommand("USER");
}

/**
 * Registers a user to the server
 *
 * @param user The user to register.
 */
void registerUser(User& user) {
    User::command_iterator it_end = user.getCommandsEnd();
    /* wait for all commands needed for registration */
    if (user.getCommands().size() > 3) {
        User::command_iterator it = user.findCommand("PASS");
        /* if user did not send a PASS command or if PASS is empty, send error message */
        if (it != it_end && it->size() > 1) {
            handlePASS(user, it->at(1));
        } else {
            handlePASS(user, "");
        }
        std::vector<std::vector<std::string> > commands = user.getCommands();
        for (std::vector<std::vector<std::string> >::size_type i(0); i < commands.size(); i++) {
            if (commands[i].size() > 0) {
                if (commands[i][0] == "CAP") {
                    handleCAP(user, commands[i]);
                } else if (commands[i][0] == "NICK") {
                    if (commands[i].size() > 1) {
                        handleNICK(user, commands[i][1]);
                    } else {
                        handleNICK(user, "");
                    }
                } else if (commands[i][0] == "USER") {
                    handleUSER(user, commands[i]);
                }
            }
        }
        user.setRegistered(TRUE);
        if (user.isAuthenticated())
            sendWelcome(user);
    }
}

/**
 * Sends a welcome message to the user.
 *
 * @param user The user to send the message to.
 */
void sendWelcome(User& user) {
    std::string time = displayTimestamp();
        std::ifstream file("motd/motd.txt");
    std::string message = "";
    if (file.is_open()) {
        std::string line;
        while (getline(file, line)) {
            message = std::string(RPL_MOTD) + " :- " + line + "\r\n";
            TCPserver::sendReply(user, message);
        }
        file.close();
    }
    message = std::string(RPL_WELCOME) + " " + user.getNickname() + "\r\n" + "Welcome to the Internet Relay Network, " + user.getNickname() + "[!" + user.getUsername() + "@" + user.getHostname() + "]\r\n";
    TCPserver::sendReply(user, message);
    message = std::string(RPL_YOURHOST) + " " + SERVER_NAME + " :Your host is " + SERVER_NAME + ", running version " + SERVER_VERSION + "\r\n";
    TCPserver::sendReply(user, message);
    message = std::string(RPL_CREATED) + " " + SERVER_NAME + " :This server was created at " + time + "\r\n";
    TCPserver::sendReply(user, message);
    message = std::string(RPL_MYINFO) + " " + SERVER_NAME + " " + SERVER_VERSION + " " + SERVER_USER_MODES + " " + SERVER_CHANNEL_MODES + "\r\n";
    TCPserver::sendReply(user, message);
    message = std::string(RPL_ISUPPORT) + " " + SERVER_NAME + " " + SERVER_ISUPPORT + "\r\n";
}