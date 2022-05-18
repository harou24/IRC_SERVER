#include "cmd_controller.hpp"

CmdController::CmdController(): server_(NULL) { }

CmdController::CmdController(IrcServer &server): server_(&server)
{   
    parser_ = new Parser();
    cmds_.insert(std::pair<CommandType, t_ft_ptr>(CAP_LS, t_ft_ptr (cap_ls)));
    cmds_.insert(std::pair<CommandType, t_ft_ptr>(NICK, t_ft_ptr (nick)));
    cmds_.insert(std::pair<CommandType, t_ft_ptr>(MODE, t_ft_ptr (mode)));
    cmds_.insert(std::pair<CommandType, t_ft_ptr>(USER, t_ft_ptr (user)));
    cmds_.insert(std::pair<CommandType, t_ft_ptr>(PING, t_ft_ptr (ping)));
    cmds_.insert(std::pair<CommandType, t_ft_ptr>(PONG, t_ft_ptr (pong)));
    cmds_.insert(std::pair<CommandType, t_ft_ptr>(PRIVMSG, t_ft_ptr (privmsg)));
    cmds_.insert(std::pair<CommandType, t_ft_ptr>(QUIT, t_ft_ptr (quit)));
    cmds_.insert(std::pair<CommandType, t_ft_ptr>(AWAY, t_ft_ptr (away)));
    cmds_.insert(std::pair<CommandType, t_ft_ptr>(JOIN, t_ft_ptr (join)));
    cmds_.insert(std::pair<CommandType, t_ft_ptr>(INVITE, t_ft_ptr (invite)));
    cmds_.insert(std::pair<CommandType, t_ft_ptr>(PART, t_ft_ptr (part)));
    cmds_.insert(std::pair<CommandType, t_ft_ptr>(KICK, t_ft_ptr (kick)));
    cmds_.insert(std::pair<CommandType, t_ft_ptr>(PASS, t_ft_ptr (pass)));
    cmds_.insert(std::pair<CommandType, t_ft_ptr>(TOPIC, t_ft_ptr (topic)));
    cmds_.insert(std::pair<CommandType, t_ft_ptr>(NOTICE, t_ft_ptr (notice)));
    cmds_.insert(std::pair<CommandType, t_ft_ptr>(UNKNOWN, t_ft_ptr (unknown)));
}

CmdController::~CmdController() 
{
    delete(parser_);
}

void CmdController::execute(Message *m)
{
    #if 1
        print("DEBUG", "execute...");
    #endif
    currentMsg_ = m;
    parser_->parse(m->getData());
    if (parser_->getCommand() == UNKNOWN)
        return ;
    std::string reply = cmds_[parser_->getCommand()](*this);
    TcpStream *s = m->getStreamPtr();
    #if 1
        if (s){
            std::stringstream ss;
            ss << "STREAM:\n" << *s;
            print("DEBUG", ss.str());
        }
    #endif

    if (!reply.empty())
    {
        std::cout << "REPLY------------------------>" << reply << "\n";
        m->getStream().send(reply, reply.length());
    }
    /*
    if (reply == ":Password incorrect\n")
        sleep(2);
        server_->disconnect(m->getStream().getSd());
        */
}

Message& CmdController::getCurrentMsg() const
{
    return *currentMsg_;
}

Parser& CmdController::getParser() const
{
    return *parser_;
}

IrcServer&  CmdController::getServer() const
{
    return *server_;
}