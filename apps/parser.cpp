#include "parser.hpp"
#include <iostream>

int main()
{
    Parser   T;
    
    T.parse("USER name hostname servername :real name");

    IArgs A = T.getArgument();

    std::cout << T.getCommand() << std::endl;
    std::cout << T.getRaw() << std::endl;
    std::cout << A.arg1 << std::endl;
    std::cout << A.arg2 << std::endl;
    std::cout << A.arg3 << std::endl;
    std::cout << A.arg4 << std::endl;

}
