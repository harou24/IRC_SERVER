#include "Table.hpp"
#include "Row.hpp"

#include <vector>
#include <string>
#include <iostream>

int main(void)
{
    Row t(std::vector<std::string> (10, std::string("hello")), 6);
    std::cout << t << "\n";
    return (0);
}