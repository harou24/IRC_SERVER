#ifndef CMD_CONTROLLER_HPP
# define CMD_CONTROLLER_HPP

# include "commands.hpp"
# include "parser.hpp"
# include "irc_server.hpp"
# include "print.hpp"

# include <map>

class Parser;
class IrcServer;

class CmdController {

    private:
        typedef std::string (*t_ft_ptr)(const CmdController*);
        std::map<int, t_ft_ptr> cmds_;
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

        Parser& getParser();
        IrcServer& getServer();
};

#endif