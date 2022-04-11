#ifndef CMD_CONTROLLER_HPP
# define CMD_CONTROLLER_HPP

# include "Server.hpp"
#include "commands.hpp"

# include <map>


typedef std::string (*t_ft_ptr)(const Server* const);

class CmdController {

    private:
        std::map<CommandType, t_ft_ptr> cmds_;
        const Server* const server_;
        CmdController();


    public:
        CmdController(const Server* const server);
        ~CmdController();

        void execute(CommandType type);

};

#endif