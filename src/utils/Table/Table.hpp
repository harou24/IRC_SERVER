#ifndef TABLE_HPP
# define TABLE_HPP

# include "Row.hpp"

class Table {

    public:
        Table(void);
        Table(std::vector<Row> rows);
        ~Table(void);

        void    print(void);

    private:
        std::vector<Row> rows_;
};

#endif