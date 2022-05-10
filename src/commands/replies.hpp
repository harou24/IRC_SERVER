#ifndef REPLIES_HPP
# define REPLIES_HPP

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

# define RPL_UMODEIS(host, args) ":" + args.arg1 + "!" + args.arg1 + "@" + host + " MODE " + args.arg1 + " :" + args.arg2 +  "\n"
# define PRIV_MESSAGE(nick, nick2, user, host, message) ":" + nick + "!" + user + "@" + host + " PRIVMSG " + nick2 + " " + message + "\n"
# define RPL_AWAY(nick, nick2, msg) ":" + std::string(HOST) + " 301 " + nick2 + " " + nick + " " + msg + "\n"
# define RPL_UNAWAY() ":" + std::string(HOST) + " 305 :You are no longer marked as being away\n"
# define RPL_NOAWAY() ":" + std::string(HOST) + " 306 :You have been marked as being away\n"
# define RPL_JOIN(cl, channel) ":" + cl->getNick() + "!~" + cl->getHost() + "@" + cl->getServer() + " JOIN :" + channel + "\n"
# define RPL_NAMREPLY(nick, channel) ":" + std::string(HOST) + " 353 " + nick + " = " + channel + " :"
# define RPL_ENDOFNAMES(nick, channel) ":" + std::string(HOST) + " 366 " + nick + " " + channel + " :End of /NAMES list\n"
# define RPL_INVITING(nick, nick2, channel) ":" + std::string(HOST) + " 341 " + nick + " " + nick2 + " " + channel + "\n"
# define INVITE_MESSAGE(nick, nick2, user, host, channel) ":" + nick + "!" + user + "@" + host + " INVITE " + nick2 + " " + channel + "\n"
# define ERR_NOSUCHNICK(nick, nick2) ":" + std::string(HOST) + " 401 " + nick + " " + nick2 + " :No such nick/channel\n"
# define RPL_PART(cl, channel) ":" + cl->getNick() + "!~" + cl->getHost() + "@" + cl->getServer() + " PART " + channel + " :\n"
# define RPL_QUIT(cl, msg) ":" + cl->getNick() + "!~" + cl->getHost() + "@" + cl->getServer() + " QUIT :Quit: " + &msg[1] + "\n"

# define ERR_NOSUCHCHANNEL(nick, channel) ":" + std::string(HOST) + " 403 " + nick + " " + channel + " :No such channel\n"
# define ERR_NOTONCHANNEL(nick, channel) ":" + nick + " " + channel + " You're not on that channel\n"
# define ERR_NEEDMOREPARAMS(nick, channel) ":" + std::string(HOST) + " 461 " + nick + " " + channel + " :Not enough parameters\n"
# define ERR_USERSDONTMATCH(nick) ":" + std::string(HOST) + " 502 " + nick + " :Can't change mode for other users\n"
# define ERR_CHANOPRIVSNEEDED(channel) ": 482 " + channel + " :You're not channel operator\n"
# define ERR_INVITEONLYCHAN(nick, channel) ":" + std::string(HOST) + " 473 " + nick + " " + channel + " :Cannot join channel (+i)\n"

#endif