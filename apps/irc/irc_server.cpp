#include "irc_server.hpp"

int     main()
{
    IrcServer   S(8080, "lalala");

    S.start();
    return 0;
}