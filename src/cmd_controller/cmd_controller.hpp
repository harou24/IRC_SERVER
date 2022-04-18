#ifndef CMD_CONTROLLER_HPP
# define CMD_CONTROLLER_HPP

# include "irc_server.hpp"

# include <map>



class CmdController {

    private:
        typedef std::string (*t_ft_ptr)(const CmdController*);
        std::map<CommandType, t_ft_ptr> cmds_;
        IrcServer* server_;
        Parser* parser_;
        
        CmdController();


    public:
        CmdController(IrcServer* server);
        CmdController(IrcServer* server, Message *m);
        ~CmdController();

        void execute(Message *m);

};

#endif