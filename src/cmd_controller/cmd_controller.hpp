#ifndef CMD_CONTROLLER_HPP
# define CMD_CONTROLLER_HPP

# include "server.hpp"
# include "commands.hpp"

# include <map>


typedef std::string (*t_ft_ptr)(const Server* const);

class CmdController {

    private:
        std::map<CommandType, t_ft_ptr> cmds_;
        IrcServer* server_;
        CmdController();


    public:
        CmdController(IrcServer* server);
        CmdController(IrcServer* server, Message *m);
        ~CmdController();

        void execute(Message *m);
        void process(Message *msg);

};

#endif