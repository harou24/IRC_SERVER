#include "cmd_controller.hpp"

CmdController::CmdController(): server_(NULL) { }

CmdController::CmdController(IrcServer* server): server_(server)
{   
    parser_ = new Parser();
    cmds_.insert(std::pair<CommandType, t_ft_ptr>(CAP_LS, t_ft_ptr (cap_ls)));
    cmds_.insert(std::pair<CommandType, t_ft_ptr>(NICK, t_ft_ptr (nick)));
    cmds_.insert(std::pair<CommandType, t_ft_ptr>(MODE, t_ft_ptr (nick)));
    cmds_.insert(std::pair<CommandType, t_ft_ptr>(USER, t_ft_ptr (user)));
    cmds_.insert(std::pair<CommandType, t_ft_ptr>(PING, t_ft_ptr (ping)));
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
    std::cout << "CMD->" << parser_->getCommand() << "\n";
    std::string reply = cmds_[parser_->getCommand()](this);
    //if (!reply.empty())
    //    m->getStream().send(reply, reply.length());
}

Message* CmdController::getCurrentMsg()
{
    return currentMsg_;
}

Parser& CmdController::getParser()
{
    return *parser_;
}

IrcServer&  CmdController::getServer()
{
    return *server_;
}