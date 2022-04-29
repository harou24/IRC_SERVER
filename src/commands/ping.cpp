#include "commands.hpp"
#include <ctime>

std::string gen_random(const int len) {
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "!@#$%^&*()-_+=~";
    std::string tmp_s;
    tmp_s.reserve(len);

    for (int i = 0; i < len; ++i) {
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
    }
    
    return tmp_s;
}

std::string    ping(CmdController* controller)
{
    srand((unsigned)time(NULL) * getpid());
    if (controller)
        std::cout << "PING\n";
    return std::string(gen_random(rand() % 100));
}