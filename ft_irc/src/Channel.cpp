#include "../inc/Channel.hpp"

Bans::Bans(std::string maskname, std::string user, time_t const &timeset) : _maskname(maskname), _user(user), _time(timeset) {}
Bans::Bans(Bans const &src) : _time(src.getTime()){
    _maskname = src.getMaskName();
    _user = src.getUser();

}
Bans::~Bans() {}

Channel::Channel() { }

Channel::Channel(std::string const& name)
    : _name(name), _mode("nt"), _limit(0), _creationTime(time(NULL)) { }

Channel::~Channel() {
    _users.clear();
    _operators.clear();
    for (std::vector<Bans *>::iterator it = _bans.begin(); it != _bans.end(); it++)
        delete *it;
    _bans.clear();
    _inviteList.clear();
}

Channel::Channel(Channel const& channel)
    : _name(channel._name), _topic(channel._topic), _mode(channel._mode),
      _key(channel._key), _limit(channel._limit), _creationTime(channel._creationTime),
      _users(channel._users), _operators(channel._operators), _bans(channel._bans) { }

Channel &Channel::operator=(Channel const& channel) {
    if (this != &channel) {
        _name = channel._name;
        _topic = channel._topic;
        _mode = channel._mode;
        _key = channel._key;
        _limit = channel._limit;
        _creationTime = channel._creationTime;
        _users = channel.getUsers();
        _operators = channel.getOperators();
        _bans = channel.getBans();
    }
    return *this;
}

/* Getters */
std::string Channel::getUsersNames() const {
    std::string users_names;
    for (std::map<int, User*>::const_iterator it = _users.begin(); it != _users.end(); ++it) {
        if (isChannelOperator(it->second))
            users_names += "@";
        else if (isVoiced(it->second))
            users_names += "+";
        users_names += it->second->getNickname() + " ";
    }
    return users_names;
}

User& Channel::getUserByNickname(std::string const& nickname) {
    for (std::map<int, User*>::iterator it = _users.begin(); it != _users.end(); ++it) {
        if (it->second->getNickname() == nickname) {
            return *it->second;
        }
    }
    throw std::runtime_error("Channel::getUserByNickname() :User not found");
}

std::vector<Bans *> Channel::getBans() const { 
    return _bans; }
/* Setters */
void Channel::setMode(char const& mode, int const& add) {
    if (add) {
        if (_mode.find(mode) == std::string::npos)
            _mode += mode;
    } else {
        if (_mode.find(mode) != std::string::npos)
            _mode.erase(_mode.find(mode), 1);
    }
}

void Channel::addOperator(User* user) {
    std::cout << displayTimestamp() << "-!- [CHANNEL " << _name << "] " << user->getNickname() << " is now an operator" << std::endl;
    _operators.push_back(user);
}
void Channel::removeOperator(User* user) {
    std::cout << displayTimestamp() << "-!- [" << _name << "] " << user->getNickname() << " is no longer an operator" << std::endl;
    _operators.erase(std::remove(_operators.begin(), _operators.end(), user), _operators.end());
}

bool Channel::isChannelOperator(User* user) const {
    for (std::vector<User*>::const_iterator it = _operators.begin(); it != _operators.end(); ++it) {
        if ((*it)->getFullname() == user->getFullname()) {
            return true;
        }
    }
    return false;
}

void Channel::addBan(std::string maskname, User *user) {
    std::cout << displayTimestamp() << "-!- [CHANNEL " << _name << "] " << maskname << " is now banned" << std::endl;
    Bans *ban = new Bans(maskname, user->getFullname(), time(NULL));
    _bans.push_back(ban);
}

void Channel::removeBan(std::string user) {
    std::cout << displayTimestamp() << "-!- [CHANNEL " << _name << "] " << user << " is no longer banned" << std::endl;
    std::vector<Bans*>::iterator it = _bans.begin();
    for (; it != _bans.end(); it++) {
        if ((*it)->getMaskName() == user)
            break;
    }
    delete *it;
    _bans.erase(it);
}

void Channel::addToInvitList(User* user) {
    std::cout << displayTimestamp() << "-!- [CHANNEL " << _name << "] " << user->getNickname() << " is now invited" << std::endl;
    _inviteList.push_back(user);
}

void Channel::removeFromInvitList(User* user) {
    std::cout << displayTimestamp() << "-!- [CHANNEL " << _name << "] " << user->getNickname() << " is no longer invited" << std::endl;
    _inviteList.erase(std::remove(_inviteList.begin(), _inviteList.end(), user), _inviteList.end());
}

void Channel::addVoiced(User* user) {
    std::cout << displayTimestamp() << "-!- [CHANNEL " << _name << "] " << user->getNickname() << " is now voiced" << std::endl;
    _voiced.push_back(user);
}

void Channel::removeVoiced(User* user) {
    std::cout << displayTimestamp() << "-!- [CHANNEL " << _name << "] " << user->getNickname() << " is no longer voiced" << std::endl;
    _voiced.erase(std::remove(_voiced.begin(), _voiced.end(), user), _voiced.end());
}

/* Users */
void Channel::addUser(User* user) { _users.insert(std::pair<int, User*>(user->getFD(), user)); }
void Channel::removeUser(User* user) { _users.erase(user->getFD()); }

bool Channel::isUserInChannel(User const& user) const { return _users.find(user.getFD()) != _users.end(); }
bool Channel::isBanned(std::string user) const {
    for (std::vector<Bans*>::const_iterator it = _bans.begin(); it != _bans.end(); ++it) {
        if (user == (*it)->getMaskName()) {
            return true;
        }
    }
    return false;
}

bool Channel::isInvited(User* user) const {
    for (std::vector<User*>::const_iterator it = _inviteList.begin(); it != _inviteList.end(); ++it) {
        if ((*it)->getFullname() == user->getFullname()) {
            return true;
        }
    }
    return false;
}

bool Channel::isVoiced(User *user) const {
    for (std::vector<User*>::const_iterator it = _voiced.begin(); it != _voiced.end(); ++it) {
        if ((*it)->getFullname() == user->getFullname()) {
            return true;
        }
    }
    return false;
}