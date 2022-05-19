#include "commands.hpp"

#include <ctime>
#include <algorithm>

std::string generateRandom(const int len)
{
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "!@#$%^&*()-_+=~";
    std::string str;
    str.reserve(len);

    for (int i = 0; i < len; ++i) 
    {
        str += alphanum[rand() % (sizeof(alphanum) - 1)];
    }
    return str;
}

std::string    cap_ls(const CmdController& controller)
{
    srand((unsigned)time(NULL) * getpid());
    #if 1
            print("DEBUG", "CAP LS cmd! " + controller.getCurrentMsg().getData());
    #endif
    return std::string(NOTICE(std::string(HOST)) + "CAP * LS :\n");
}
