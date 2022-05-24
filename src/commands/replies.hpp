#ifndef REPLIES_HPP
# define REPLIES_HPP

# include <ctime>


# define NOTICE(server) server + " NOTICE * :*** Looking up your hostname...\n"

# define RPL_WELCOME(nick, args) ":" + args.arg3 + " 001 " + nick + "\n: Welcome to the Internet Relay Network\n" + nick + "!" + args.arg1 + "@" + args.arg2 + "\n"
# define RPL_YOURHOST(args) ":Your host is " + args.arg3 + ", running version 1.0\n"
# define RPL_CREATED ":This server was created 12.54.22 Apr 06 2022\n"
# define LOGO_P1 "          _          _            _                     \n \
        /\\ \\       /\\ \\        /\\ \\     \n\
         \\ \\ \\     /  \\ \\      /  \\ \\    \n\
         /\\ \\_\\   / /\\ \\ \\    / /\\ \\ \\   \n\
        / /\\/_/  / / /\\ \\_\\  / / /\\ \\ \\  \n\
       / / /    / / /_/ / / / / /  \\ \\_\\ \n\
      / / /    / / /__\\/ / / / /    \\/_/ \n\
     / / /    / / /_____/ / / /          \n\
 ___/ / /__  / / /\\ \\ \\  / / /________  \n\
/\\__\\/_/___\\/ / /  \\ \\ \\/ / /_________\\  \n\
\\/_________/\\/_/    \\_\\/\\/____________/   \n\n"

# define LOGO_P2 "                            _ _  \n \
       //||\\\\   ///||\\   /.-. | \n\
        ` @ @\\     a a   ||o_o|| \n\
           >        _)   || = || \n\
           -        ~      ' '   \n\
       haroutioun eutienne evita\n\n"


# define PRIV_MESSAGE(nick, nick2, user, host, message) ":" + nick + "!" + user + "@" + host + " PRIVMSG " + nick2 + " " + message + "\n"
# define INVITE_MESSAGE(nick, nick2, user, host, channel) ":" + nick + "!" + user + "@" + host + " INVITE " + nick2 + " " + channel + "\n"
# define NOTICE_MESSAGE(nick, nick2, user, host, message) ":" + nick + "!" + user + "@" + host + " NOTICE " + nick2 + " " + message + "\n"

# define RPL_JOIN(cl, channel) ":" + cl->getNick() + "!~" + cl->getHost() + "@" + cl->getServer() + " JOIN :" + channel + "\n"
# define RPL_KICK(cl, channel, user, msg) ":" + cl->getNick() + "!~" + cl->getHost() + "@" + cl->getServer() + " KICK " + channel + " " + user + " " + msg + "\n"
# define RPL_PART(cl, channel) ":" + cl->getNick() + "!~" + cl->getHost() + "@" + cl->getServer() + " PART " + channel + " :\n"
# define RPL_QUIT(cl, msg) ":" + cl->getNick() + "!~" + cl->getHost() + "@" + cl->getServer() + " QUIT :Quit: " + &msg[1] + "\n"
# define RPL_TOPICSET(cl, channel, message) ":" + cl->getNick() + "!~" + cl->getHost() + "@" + cl->getServer() + " TOPIC " + channel + " " + message + "\n"

# define RPL_AWAY(nick, nick2, msg) ":" + std::string(HOST) + " 301 " + nick2 + " " + nick + " " + msg + "\n"
# define RPL_UNAWAY() ":" + std::string(HOST) + " 305 :You are no longer marked as being away\n"
# define RPL_NOAWAY() ":" + std::string(HOST) + " 306 :You have been marked as being away\n"
# define RPL_UMODEIS(cl, args) ":" + cl->getNick() + "!~" + cl->getHost() + "@" + cl->getServer() + " MODE " + args.arg1 + " " + args.arg2 + " :" + args.arg4 + "\n"    /*  221  */
# define RPL_UMODEIS2(cl, args) ": 324 " + cl->getNick() + " " + args.arg1 + " :" + args.arg3 + "\n"
# define RPL_CREATIONTIME(nick, channel, time) ":" + std::string(HOST) + " 329 " + nick + " " + channel + " :" + time + "\n"
# define RPL_NOTOPIC(nick, channel) ": 331 " + nick + " " + channel + " :No topic is set.\n"
# define RPL_TOPIC(nick, channel, message) ": 332 " + nick + " " + channel + " " + message + "\n"
# define RPL_TOPICWHOTIME(nick, channel, topic) ": 333 " + nick + " " + channel + " " + topic.topic_nick + "!~" + topic.writer->getHost() + "@" + topic.writer->getServer() + " :" + topic.creationTimeTopic + "\n" 
# define RPL_INVITING(nick, nick2, channel) ":" + std::string(HOST) + " 341 " + nick + " " + nick2 + " " + channel + "\n"
# define RPL_NAMREPLY(nick, channel) ":" + std::string(HOST) + " 353 " + nick + " = " + channel + " :"
# define RPL_ENDOFNAMES(nick, channel) ":" + std::string(HOST) + " 366 " + nick + " " + channel + " :End of /NAMES list\n"
# define RPL_BANLIST(user, nick, channel, name, time)  ":" + std::string(HOST) + " 367 " + user + " " + channel + " " + name + " " + nick + " :" + time + "\n"
# define RPL_ENDOFBANLIST(nick, channel) ":" + std::string(HOST) + " 368 " + nick + " " + channel + " :End of channel ban list\n"

# define ERR_NOSUCHNICK(nick, nick2) ":" + std::string(HOST) + " 401 " + nick + " " + nick2 + " :No such nick/channel\n"
# define ERR_NOSUCHCHANNEL(nick, channel) ":" + std::string(HOST) + " 403 " + nick + " " + channel + " :No such channel\n"
# define ERR_CANNOTSENDTOCHAN(nick, channel)  ":" + std::string(HOST) + " 404 " + nick + " " + channel + " :You cannot send external messages to this channel whilst the +n (noextmsg) mode is set.\n"
# define ERR_CANNOTSENDTOCHANBAN(nick, channel)  ":" + std::string(HOST) + " 404 " + nick + " " + channel + " :You cannot send messages to this channel whilst banned.\n"
# define ERR_NOTONCHANNEL(nick, channel) ":" + nick + " " + channel + " You're not on that channel\n"
# define ERR_USERNOTINCHANNEL(nick, nick2, channel)  ":" + std::string(HOST) + " 441 " + nick + " " + nick2 + " " + channel + " :They are not on that channel\n"
# define ERR_NEEDMOREPARAMS(nick, channel) ":" + std::string(HOST) + " 461 " + nick + " " + channel + " :Not enough parameters\n"
# define ERR_CHANNELISFULL(nick, channel) ":" + std::string(HOST) + " 471 " + nick + " " + channel + " :Cannot join channel (+l)\n"
# define ERR_INVITEONLYCHAN(nick, channel) ":" + std::string(HOST) + " 473 " + nick + " " + channel + " :Cannot join channel (+i)\n"
# define ERR_BANNEDFROMCHAN(nick, channel) ":" + std::string(HOST) + " 474 " + nick + " " + channel + " :Cannot join channel (+b)\n"
# define ERR_BADCHANNELKEY(nick, channel) ":" + std::string(HOST) + " 475 " + nick + " " + channel + " :Cannot join channel (+k)\n"
# define ERR_CHANOPRIVSNEEDED(nick, channel) ":" + std::string(HOST) + " 482 " + nick + " " + channel + " :You must be a channel half-operator\n"

# define ERR_USERSDONTMATCH(nick) ":" + std::string(HOST) + " 502 " + nick + " :Can't change mode for other users\n"
# define ERR_HELPTOPIC(nick, command) ": 650 " + nick + " " + command + " :<channel> [:<topic>]\n"

# define ERR_HELPOPERATOR(nick, channel) nick + " " + channel + " :You must specify a parameter for the op mode. Syntax: <nick>.\n"

#endif