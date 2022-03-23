#include "Table.hpp"

#include <iostream>

Table::Table(void) { }

Table::Table(std::vector<Row> rows): rows(rows) { }

Table::~Table(void) { }

void    Table::print(void)
{
    std::vector<Row>::iterator it;
    for (it = this->rows.begin(); it < this->rows.end(); it++)
    {
        std::cout << *it << " | ";
    }
}