#include "IrcServer.hpp"

int     main(){
    IrcServer   S(8080, "lalala");

    S.processMessage();
    return 0;
}