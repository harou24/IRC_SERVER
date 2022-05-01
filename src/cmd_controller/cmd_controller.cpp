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
    cmds_.insert(std::pair<CommandType, t_ft_ptr>(PONG, t_ft_ptr (pong)));
    cmds_.insert(std::pair<CommandType, t_ft_ptr>(UNKNOWN, t_ft_ptr (unknown)));
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
    if (parser_->getCommand() == UNKNOWN)
        return ;
    std::string reply = cmds_[parser_->getCommand()](this);
    TcpStream *s = m->getStreamPtr();
    if (s)
        std::cout << "STREAM STREAM->"<< *s << "\n";

    if (!reply.empty())
        m->getStream().send(reply, reply.length());
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