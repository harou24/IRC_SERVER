#include "commands.hpp"

#include <ctime>
#include <algorithm>

std::string gen_random(const int len)
{
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "!@#$%^&*()-_+=~";
    std::string tmp_s;
    tmp_s.reserve(len);

    for (int i = 0; i < len; ++i) 
    {
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
    }
    return tmp_s;
}

std::string    cap_ls(const CmdController& controller)
{
    srand((unsigned)time(NULL) * getpid());
    #if 1
            print("DEBUG", "CAP LS cmd! " + controller.getCurrentMsg().getData());
    #endif
    return std::string(NOTICE(std::string(HOST)) + "CAP * LS :\nPING : " + gen_random(rand() % 10 + 5) + "\n");
}
