#include "cmd_controller.hpp"


CmdController::CmdController(): server_(NULL) { }

CmdController::CmdController(IrcServer* server): server_(server)
{ 
    t_ft_ptr ft_nick = t_ft_ptr (nick);
    cmds_.insert(std::pair<CommandType, t_ft_ptr>(NICK, ft_nick));
}

CmdController::~CmdController() { }

void CmdController::execute(Message *m)
{ 
    if (m)
        std::cout << "hey\n";

}
//void CmdController::process(Message *m) { }
