#ifndef RPL_CODES_HPP
#define RPL_CODES_HPP

#pragma once

/* General */
#define ERR_UNKNOWNCOMMAND "421"
#define ERR_NEEDMOREPARAMS "461"
#define ERR_NOTREGISTERED "451"

/* Welcome replies */
#define RPL_WELCOME "001"
#define RPL_YOURHOST "002"
#define RPL_CREATED "003"
#define RPL_MYINFO "004"
#define RPL_ISUPPORT "005"

/* CAP replies */
#define ERR_INVALIDCAPCMD "410"

/* PASS replies */
#define ERR_PASSWDMISMATCH "464"

/* NICK replies */
#define ERR_NONICKNAMEGIVEN "431"
#define ERR_ERRONEUSNICKNAME "432"
#define ERR_NICKNAMEINUSE "433"
#define ERR_ALREADYREGISTRED "462"

/* WHOIS replies */
#define RPL_WHOISUSER "311"
#define RPL_WHOISSERVER "312"
#define RPL_WHOISIDLE "317"
#define RPL_ENDOFWHOIS "318"
#define RPL_WHOISCHANNEL "319"
#define ERR_NOSUCHNICK "401"

/* MODE replies */
#define ERR_NOSUCHNICK "401"
#define ERR_UMODEUNKNOWNFLAG "501"
#define ERR_USERSDONTMATCH "502"
#define RPL_UMODEIS "221"
#define RPL_CHANNELMODEIS "324"
#define RPL_CREATIONTIME "329"
#define RPL_BANLIST "367"
#define RPL_ENDOFBANLIST "368"

/* MOTD replies */
#define RPL_MOTDSTART "375"
#define RPL_MOTD "372"
#define RPL_ENDOFMOTD "376"

/* LUSERS replies */
#define RPL_LUSERCLIENT "251"
#define RPL_LUSEROP "252"
#define RPL_LUSERUNKNOWN "253"
#define RPL_LUSERCHANNELS "254"
#define RPL_LUSERME "255"
#define RPL_LOCALUSERS "265"
#define RPL_GLOBALUSERS "266"

/* JOIN replies */
#define ERR_USERONCHANNEL "443"
#define ERR_NOSUCHCHANNEL "403"
#define ERR_TOOMANYCHANNELS "405"
#define ERR_BANNEDFROMCHAN "474"
#define ERR_INVITEONLYCHAN "473"
#define ERR_BADCHANNELKEY "475"
#define ERR_CHANNELISFULL "471"
#define ERR_BADCHANMASK "476"
#define RPL_TOPIC "332"
#define RPL_TOPICWHOTIME "333"
#define RPL_NAMREPLY "353"
#define RPL_ENDOFNAMES "366"

/* TOPIC replies */
#define ERR_NOTONCHANNEL "442"
#define RPL_NOTOPIC "331"

/* OPERATOR replies */
#define ERR_CHANOPRIVSNEEDED "482"

/* PRIVMSG replies */
#define RPL_PRIVMSG "301"
#define RPL_NOTICE "304"
#define ERR_CANNOTSENDTOCHAN "404"

/* WHO replies */
#define RPL_WHOREPLY "352"
#define RPL_ENDOFWHO "315"

/* KICK BAN replies */
#define ERR_USERNOTINCHANNEL "441"
#define ERR_NOTONCHANNEL "442"

/* LIST replies */
#define RPL_LISTSTART "321"
#define RPL_LIST "322"
#define RPL_LISTEND "323"

/* KILL replies */
#define ERR_NOPRIVILEGES "481"
#define ERR_CANTKILLSERVER "483"

/* OPER replies */
#define RPL_YOUREOPER "381"
#define ERR_NOOPERHOST "491"

#endif // RPL_CODES_HPP