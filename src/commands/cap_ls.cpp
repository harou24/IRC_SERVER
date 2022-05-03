#include "commands.hpp"

#include <ctime>
#include <algorithm>

#define NOTICE(server) server + " NOTICE * :*** Looking up your hostname...\n"

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

std::string    cap_ls(CmdController* controller)
{
    srand((unsigned)time(NULL) * getpid());
    #if 1
        if (controller)
            print("DEBUG", "CAP LS cmd!");
    #endif
    std::string s =  NOTICE(std::string(HOST));
    s += "CAP * LS :\nPING : " + gen_random(rand() % 10 + 5) + "\n";
    #if 1
        print("DEBUG", s);
    #endif
    return s;
    // return std::string("127.0.0.1 CAP LS :\nPING : " + gen_random(rand() % 10));
}
