#ifndef REPLIES_HPP
# define REPLIES_HPP


#define NOTICE(server) server + " NOTICE * :*** Looking up your hostname...\n"

#define RPL_WELCOME(nick, args) ":" + args.arg3 + " 001 " + nick + "\n: Welcome to the Internet Relay Network\n" + nick + "!" + args.arg1 + "@" + args.arg2 + "\n"
#define RPL_YOURHOST(args) ":Your host is " + args.arg3 + ", running version 1.0\n"
#define RPL_CREATED ":This server was created 12.54.22 Apr 06 2022\n"
#define LOGO_P1 "          _          _            _                     \n \
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
#define LOGO_P2 "                            _ _  \n \
       //||\\\\   ///||\\   /.-. | \n\
        ` @ @\\     a a   ||o_o|| \n\
           >        _)   || = || \n\
           -        ~      ' '   \n\
       haroutioun eutienne evita\n\n"

// #define RPL_UMODEIS(host, args) ""
#define RPL_UMODEIS(host, args) ":" + args.arg1 + "!" + args.arg1 + "@" + host + " MODE " + args.arg1 + " :" + args.arg2 +  "\n"

#endif