#include "Row.hpp"
#include "colors.h"

#include <iostream>
Row::Row(void) { }

Row::Row(std::vector<std::string> elements, std::size_t length): elements(elements), cell_length(length) { }

Row::~Row(void) { }

const std::vector<std::string>&    Row::getWords(void) const
{
    return this->elements;
}

std::size_t                        Row::getCellLength(void) const
{
    return this->cell_length;
}

std::string                        Row::getCellAtIndexAsStr(std::size_t index) const
{
    std::string str("");

    if (index < this->elements.size())
    {
        str = this->elements[index];
        if (str.length() < this->cell_length)
            str.append(this->cell_length - str.length(), ' ');
        else
        {
            str = std::string(str, 0, this->cell_length);
            str = str.replace(str.length(), 1, ".");
        }
    }
    return str;
}

std::string                        Row::getRowAsStr(void) const
{
    std::string str("");
    str += RED;

    for (std::size_t i = 0; i < this->elements.size(); i++)
    {
        str += this->getCellAtIndexAsStr(i);
        if (i != this->elements.size() - 1)
            str += " | ";
    }
    str += RESET;
    return str;
}

std::ostream &operator << (std::ostream &output, const Row &row)
{
    std::string str = row.getRowAsStr();
    output << str;
    return output;
}