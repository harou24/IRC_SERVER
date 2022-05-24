#ifndef PRINT_HPP
# define PRINT_HPP

# include <iostream>
# include <cstring>
# include "colors.h"

enum Levels{
    ERROR,
    INFO,
    DEBUG
};

#define USE 0

void    print(const char *level, std::string msg);

#endif