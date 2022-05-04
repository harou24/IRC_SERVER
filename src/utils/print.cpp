#include "print.hpp"

void    print(const char *level, std::string msg){
    const char *levels[3] = {"ERROR", "INFO", "DEBUG"};
    Levels current = static_cast<Levels>(4);
    for(size_t idx = 0; idx < sizeof(levels); idx++){
        if (strcmp(level, levels[idx]) == 0){
            current = static_cast<Levels>(idx);
            break;
        }
    }
    if (current <= USE) {
        switch (current)
        {
            case ERROR:
                std::cout << RED << "Error:\n" << RESET << msg << std::endl;
                break;
            case INFO:
                std::cout << GREEN << msg << RESET << std::endl;
                break;
            case DEBUG:
                std::cout << BLUE << "DebugInfo:\n" << RESET << msg << std::endl;
                break;
            default:
                break;
        }
    }
}