#include "Table.hpp"
#include "Row.hpp"

#include <vector>
#include <string>
#include <iostream>

int main(void)
{
    Row r1(std::vector<std::string> (10, std::string("hello")), 6);
    Row r2(std::vector<std::string> (10, std::string("one")), 6);
    Row r3(std::vector<std::string> (10, std::string("two")), 6);
    Row r4(std::vector<std::string> (10, std::string("three")), 6);

    std::vector<Row> table;
    table.push_back(r1);
    table.push_back(r2);
    table.push_back(r3);
    table.push_back(r4);
    Table t(table);

    t.print();
    return (0);
}