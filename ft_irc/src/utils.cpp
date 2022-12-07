#include "../inc/utils.hpp"

/* Check if the port is valid */
bool portIsValid(char* port) {
    int i(0);
    while (port[i]) {
        if (!std::isdigit(port[i])) {
            return false;
        }
        i++;
    }
    if (std::atoi(port) < 1024 || std::atoi(port) > 65535) {
        return false;
    }
    return true;
}

/* Display date and time */
std::string displayTimestamp() {

    time_t now = time(NULL);
    struct tm tstruct = *localtime(&now);
    char buffer[40];

    strftime(buffer, sizeof(buffer), "[%H:%M:%S] ", &tstruct);
    return buffer;
}

/* Split a string into a vector of strings */
std::vector<std::string> split(std::string const& str, std::string const& delim) {
    std::vector<std::string> result;
    size_t start(0);
    size_t end(str.find(delim));
    while (end != std::string::npos) {
        result.push_back(str.substr(start, end - start));
        start = end + delim.length();
        end = str.find(delim, start);
    }
    result.push_back(str.substr(start, end));
    return result;
}

/* Check if nickname follows the rules */
bool isNicknameValid(std::string const& nickname) {
    if (nickname.length() > MAX_NICKNAME_SIZE || nickname.length() < 1) {
        return false;
    }
    for (std::string::size_type i(0); i < nickname.length(); i++) {
        if (!std::isalnum(nickname[i]) && nickname[i] != '_') {
            return false;
        }
    }
    return true;
}

/* Check if nickname is already taken */
bool isNicknameTaken(std::string const& nickname, std::map<int, User> const& user) {
    for (std::map<int, User>::const_iterator it(user.begin()); it != user.end(); it++) {
        if (it->second.getNickname() == nickname) {
            return true;
        }
    }
    return false;
}

/* converts an integer into a string */
std::string toString(int const& i) {
    std::stringstream ss;
    ss << i;
    return ss.str();
}
