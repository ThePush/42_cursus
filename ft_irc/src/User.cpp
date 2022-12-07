#include "../inc/User.hpp"

User::User()
    : _fd(-1), _nickname(""), _username(""), _realname(""), _hostname(""), _mode(""), _isServerOperator(FALSE), _authenticated(TRUE), _registered(FALSE), _gotKilled(FALSE) { }

User::User(int const& fd)
    : _fd(fd), _nickname(""), _username(""), _realname(""), _hostname(""), _mode(""), _isServerOperator(FALSE), _authenticated(TRUE), _registered(FALSE), _gotKilled(FALSE) { }

User::User(User const& user)
    : _fd(user.getFD()), _nickname(user.getNickname()), _username(user.getUsername()), _realname(user.getRealName()), _hostname(user.getHostname()), _mode(user.getMode()), _isServerOperator(user.isServerOperator()), _authenticated(user.isAuthenticated()), _registered(user.isRegistered()), _gotKilled(user.gotKilled()) {
    _commands = user.getCommands();
    _channels = user.getUserChannels();
}

User& User::operator=(User const& user) {
    if (this != &user) {
        _fd = user.getFD();
        _nickname = user.getNickname();
        _username = user.getUsername();
        _realname = user.getRealName();
        _hostname = user.getHostname();
        _mode = user.getMode();
        _isServerOperator = user.isServerOperator();
        _authenticated = user.isAuthenticated();
        _registered = user.isRegistered();
        _gotKilled = user.gotKilled();
        _commands = user.getCommands();
        _channels = user.getUserChannels();
    }
    return *this;
}

User::~User() {
    _fd = -1;
    _commands.clear();
    _channels.clear();
}

/**
 * Adds a command to the user's command list.
 *
 * @param command The command to add to the user's history.
 */
void User::addCommand(User& user, std::string const& command) {
    std::vector<std::string> tmp;
    std::string tmp2;
    std::stringstream ss(command);
    while (ss >> tmp2) {
        tmp.push_back(tmp2);
    }
    /* if user input is not an existing command, send error messqge and return */
    if (!ISACOMMAND(tmp[0])) {
        std::cout << displayTimestamp() << "[" << _fd << "] "
                  << "[SERVER] Unknown command: " << tmp[0] << std::endl;
        std::string message = std::string(ERR_UNKNOWNCOMMAND) + " " + tmp[0] + " :Unknown command\r\n";
        TCPserver::sendReply(*this, message);
        return;
    }
    /* if user is not registered and tries a command other than registering ones, send error message and return */
    if (!isRegistered() && tmp[0] != "NICK" && tmp[0] != "USER" && tmp[0] != "PASS" && tmp[0] != "CAP") {
        std::cout << displayTimestamp() << "[" << _fd << "] "
                  << "[SERVER] User is not registered" << std::endl;
        std::string message = std::string(ERR_NOTREGISTERED) + " :You have not registered\r\n";
        TCPserver::sendReply(*this, message);
        return;
    }
    if (!isRegistered() && (user.findCommand(tmp[0]) != user.getCommandsEnd())) {
        std::cout << displayTimestamp() << "[" << _fd << "] "
                  << "[SERVER] Command already sent" << std::endl;
        std::string message = std::string(ERR_ALREADYREGISTRED) + " :Unauthorized command (already sent)\r\n";
        TCPserver::sendReply(*this, message);
        return;
    }
    _commands.push_back(tmp);
}

User::command_iterator User::findCommand(std::string const& command) {
    for (command_iterator it = _commands.begin(); it != _commands.end(); ++it) {
        if ((*it)[0] == command) {
            return it;
        }
    }
    return _commands.end();
}

void User::deleteCommand(std::string const& command) {
    for (std::vector<std::vector<std::string> >::iterator it = _commands.begin(); it != _commands.end(); ++it) {
        if ((*it)[0] == command) {
            _commands.erase(it);
            break;
        }
    }
}

void User::printCommands() const {
    for (std::vector<std::vector<std::string> >::size_type i(0); i < _commands.size(); i++) {
        for (std::vector<std::string>::size_type j(0); j < _commands[i].size(); j++) {
            std::cout << displayTimestamp() << "[" << _fd << "] [DEBUG] command[" << i << "][" << j << "]: " << _commands[i][j] << std::endl;
        }
    }
}

void User::setMode(char const& mode, int const& add) {
    if (add) {
        if (_mode.find(mode) == std::string::npos)
            _mode += mode;
    } else {
        if (_mode.find(mode) != std::string::npos)
            _mode.erase(_mode.find(mode), 1);
    }
}