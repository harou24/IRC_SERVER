#ifndef PRINT_HPP
# define PRINT_HPP

# define GREEN "\033[0;32m"
# define RED "\033[0;31m"
# define BLUE "\033[0;34m"
# define RESET "\033[0m"

# include <iostream>

enum Levels{
    ERROR,
    INFO,
    DEBUG
};

#define USE 2

void    print(const char *level, std::string msg);

#endif