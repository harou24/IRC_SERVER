#ifndef ROW_HPP
# define ROW_HPP

# include <vector>
# include <string>

class Row {
    private:
        std::vector<std::string> words;

    public:
        Row(void);
        Row(std::vector<std::string> words);
        ~Row(void);

        std::vector<std::string>    getWords(void) const;

        void    print(void);

};

std::ostream &operator << (std::ostream &output, const Row &row);

#endif