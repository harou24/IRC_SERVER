#include "cmd_controller.hpp"


CmdController::CmdController(): server_(NULL) { }

CmdController::CmdController(const Server* const server): server_(server)
{ 
    t_ft_ptr ft_nick = t_ft_ptr (nick);
    cmds_.insert(std::pair<CommandType, t_ft_ptr>(NICK, ft_nick));
}

CmdController::~CmdController() { }

//void CmdController::execute(CommandType type) { }
//void CmdController::process(Message *m) { }
