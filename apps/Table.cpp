#include "Table.hpp"
#include "Row.hpp"

#include <vector>
#include <string>
#include <iostream>

int main(void)
{
    std::vector<std::string> vec(10, std::string("hello"));
    Row t(vec);
    std::cout << t << "\n";
    t.print();
    return (0);
}