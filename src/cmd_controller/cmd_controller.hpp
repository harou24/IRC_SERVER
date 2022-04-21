#ifndef CMD_CONTROLLER_HPP
# define CMD_CONTROLLER_HPP

# include "irc_server.hpp"
# include "commands.hpp"
# include "parser.hpp"

# include <map>


class CmdController {

    private:
        typedef std::string (*t_ft_ptr)(const CmdController*);
        std::map<CommandType, t_ft_ptr> cmds_;
        IrcServer* server_;
        Parser* parser_;
        Message* currentMsg_;
        
        CmdController();


    public:
        CmdController(IrcServer* server);
        CmdController(IrcServer* server, Message *m);
        ~CmdController();

        void execute(Message *m);
        Message* getCurrentMsg();

};

#endif