#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#pragma once

#include "TCPserver.hpp"
#include "User.hpp"
#include "include.hpp"

class User;

class Bans {
    public:
        Bans(std::string maskname, std::string user, const time_t &timeset);
        Bans(Bans const &src);
        ~Bans();
        std::string getMaskName() const { return _maskname; }
        std::string getUser() const { return _user; }
        time_t const    &getTime() const { return _time; }
    private:
        std::string _maskname;
        std::string _user;
        time_t const     &_time;
};
class Channel {
public:
    Channel();
    Channel(std::string const& name);
    ~Channel();
    Channel(Channel const& channel);
    Channel &operator=(Channel const& channel);

    /* Setters */
    void setName(std::string const& name) { _name = name; }
    void setTopic(std::string const& topic) { _topic = topic; }
    void setMode(char const& mode, int const& add);
    void setKey(std::string const& key) { _key = key; }
    void setLimit(int const& limit) { _limit = limit; }
    void setCreationTime(time_t const& creation_time) { _creationTime = creation_time; }
    void setTopicCreationTime(time_t const &creation_time) { _topicCreationTime = creation_time; }
    void addOperator(User* user);
    void removeOperator(User* user);
    void addBan(std::string maskname, User *user);
    void removeBan(std::string user);
    void addToInvitList(User *user);
    void removeFromInvitList(User *user);
    void addVoiced(User *user);
    void removeVoiced(User *user);

    /* Getters */
    std::string getName() const { return _name; }
    std::string getTopic() const { return _topic; }
    std::string getMode() const { return _mode; }
    std::map<int, User*> getUsers() const { return _users; }
    User& getUserByNickname(std::string const& nickname);
    std::string getKeys() const { return _key; }
    size_t getLimit() const { return _limit; }
    time_t getCreationTime() const { return _creationTime; }
    time_t getTopicCreationTime() const { return _topicCreationTime; }
    std::string getKey() const { return _key; }
    std::string getUsersNames() const;
    std::vector<User*> getOperators() const { return _operators; }
    bool isChannelOperator(User* user) const;
    std::vector<Bans*> getBans() const; 


    /* Users */
    void addUser(User* user);
    void removeUser(User* user);
    void sendMessage(std::string const& message, User const& user);
    bool isBanned(std::string user) const;
    bool isUserInChannel(User const& user) const;
    bool isInvited(User* user) const;
    bool isVoiced(User *user) const;

private:
    std::string _name;
    std::string _topic;
    time_t      _topicCreationTime;
    std::string _mode;
    std::string _key;
    size_t _limit;
    time_t _creationTime;
    std::map<int, User*> _users;
    std::vector<User*> _operators;
    std::vector<User*> _voiced;
    std::vector<User*> _inviteList;
    std::vector<Bans*> _bans;
};

#endif // CHANNEL_HPP