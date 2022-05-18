#include "Table.hpp"

#include <iostream>

Table::Table(void) { }

Table::Table(std::vector<Row> rows): rows_(rows) { }

Table::~Table(void) { }

void    Table::print(void)
{
    std::vector<Row>::iterator it;
    for (it = this->rows_.begin(); it < this->rows_.end(); it++)
    {
        std::cout << *it << "\n";
    }
}