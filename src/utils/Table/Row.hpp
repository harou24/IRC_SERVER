#ifndef ROW_HPP
# define ROW_HPP

# include <vector>
# include <string>

class Row {

    public:
        Row();
        Row(std::size_t nb_elements,  std::size_t length = 10);
        Row(std::vector<std::string> elements, std::size_t length = 10);
        ~Row(void);

        const std::vector<std::string>& getWords(void) const;
        std::size_t getCellLength(void) const;
        std::string getCellAtIndexAsStr(std::size_t index) const;
        std::string getRowAsStr(void) const;

    private:
        std::vector<std::string> elements_;
        std::size_t cell_length_;
};

std::ostream &operator << (std::ostream &output, const Row &row);

#endif