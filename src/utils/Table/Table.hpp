#ifndef TABLE_HPP
# define TABLE_HPP

# include "Row.hpp"

class Table {
    private:
        std::vector<Row> rows;

    public:
        Table(void);
        Table(std::vector<Row> rows);
        ~Table(void);

        void    print(void);

};

#endif