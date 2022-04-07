#ifndef REPLY_MESSAGES
# define REPLY_MESSAGES


# define WELCOME "Welcome to the Internet Relay Network\n"

# define RPL_WELCOME(nick, args) ":" + args.arg3 + " 001 " + nick + "\n: " + \
WELCOME + nick + "!" + args.arg1 + "@" + args.arg2 + "\n"

# define RPL_YOURHOST(args) ":Your host is " + args.arg3 + ", running version 1.0\n"

# define RPL_CREATED ":This server was created 12.54.22 Apr 06 2022\n"

# define LOGOO "          _          _            _                     \n \
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

# define LOGO "                            _ _  \n \
       //||\\\\   ///||\\   /.-. | \n\
        ` @ @\\     a a   ||o_o|| \n\
           >        _)   || = || \n\
           -        ~      ' '   \n\
       haroutioun eutienne evita\n\n "

# define PING(str) ": " + str + " PONG " + str + " :" + str + "\n"

# define RPL_AWAY(nick, message) nick + " :" + message + "\n"

# define RPL_UNAWAY() ": You are no longer marked as being away\n"

# define RPL_NOAWAY() ": You have been marked as being away\n"

# define PRIV_MESSAGE(nick, nick2, host, message) ":" + nick + "!" + nick + "@" + \
host + "\n PRIVMSG " + nick2 + " : " + message + "\n"

#endif
