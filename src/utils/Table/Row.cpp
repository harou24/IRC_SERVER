#include "Row.hpp"
#include <iostream>

Row::Row(void) { }

Row::Row(std::vector<std::string> words): words(words) { }

Row::~Row(void) { }

void    Row::print(void)
{
    std::vector<std::string>::iterator it;
    for (it = this->words.begin(); it < this->words.end(); it++)
    {
        std::cout << *it << " | ";
    }
}

const std::vector<std::string>&    Row::getWords(void) const
{
    return this->words;
}

std::ostream &operator << (std::ostream &output, const Row &row)
{
    std::vector<const std::string>::iterator it;
    for (it = row.getWords().begin(); it < row.getWords().end(); it++)
    {
        output << *it << "\n";
    }
    return output; 
}