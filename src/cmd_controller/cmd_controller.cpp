#include "cmd_controller.hpp"
#include "commands.hpp"

CmdController::CmdController(): server_(NULL) { }

CmdController::CmdController(IrcServer* server): server_(server)
{   
    parser_ = new Parser();
    t_ft_ptr ft_nick = t_ft_ptr (nick);
    cmds_.insert(std::pair<CommandType, t_ft_ptr>(NICK, ft_nick));
}

CmdController::~CmdController() 
{
    delete(parser_);
}

void CmdController::execute(Message *m)
{
    std::cout << "execute...\n"; 
    currentMsg_ = m;
    parser_->parse(m->getData());
    if (parser_->getCommand() == NICK)
        cmds_[parser_->getCommand()](this);
}

Message* CmdController::getCurrentMsg()
{
    return currentMsg_;
}