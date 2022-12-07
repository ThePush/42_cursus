#ifndef CHANNELMODE_HPP
#define CHANNELMODE_HPP

#include "Channel.hpp"
#include "TCPserver.hpp"
#include "User.hpp"
#include "include.hpp"

class User;
class Channel;
class TCPserver;
class ChannelMode {
public:
    ChannelMode(TCPserver& server, std::vector<std::string> const& command, Channel& channel, User* user);
    ~ChannelMode();
    class CHANOPRIVSNEEDEDExeption : public std::exception {
    public:
        virtual const char* what() const throw() { return ERR_CHANOPRIVSNEEDED; }
    };
    class UMODEUNKNOWNFLAGExeption : public std::exception {
    public:
        virtual const char* what() const throw() { return ERR_UMODEUNKNOWNFLAG; }
    };

    typedef void (*fptr)(TCPserver&, std::vector<std::string> const&, int, Channel&, User*);

private:
    std::string _modes;
    int _add;
    std::map<char, fptr> _mapmodes;
};

#endif