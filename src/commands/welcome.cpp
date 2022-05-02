#include "commands.hpp"

#define RPL_WELCOME(nick, args) ":" + args.arg3 + " 001 " + nick + "\n: Welcome to the Internet Relay Network\n" + nick + "!" + args.arg1 + "@" + args.arg2 + "\n"
#define NOTICE(server) server + " NOTICE * :*** Looking up your hostname...\n"
#define LOGOO "          _          _            _                     \n \
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
#define LOGO "                            _ _  \n \
       //||\\\\   ///||\\   /.-. | \n\
        ` @ @\\     a a   ||o_o|| \n\
           >        _)   || = || \n\
           -        ~      ' '   \n\
       haroutioun eutienne evita\n\n "

std::string    welcome()
{
    std::string reply("");

    // reply = NOTICE(std::string(HOST));
    reply += std::string(LOGOO);
    reply += std::string(LOGO);
    return reply;
}