#include "commands.hpp"

#define MAX_NICK_LENGTH 9
#define ERR_NONICKNAMEGIVEN ":No nickname given\n"
#define ERR_NICKNAMEINUSE(nickname) ":" + nickname + " Nickname is already in use\n"
#define ERR_ERRONEUSNICKNAME(nickname) ":" + nickname + " Error nickname is not valid\n"

std::string    execNick(const CmdController& controller, const std::string& nickname)
{
    std::string reply("");

    TcpStream *stream = controller.getCurrentMsg().getStreamPtr();
    Client *cl = controller.getServer().getClientByStream(stream);

    if (!cl)
    {
        //create client
        std::cout << "CREATING CLIENT GO\n";
        cl = new Client("UNKNOWN", stream);
        controller.getServer().addClient(cl);
        reply = ":127.0.0.1 NOTICE * :Password NEEDED\n";
        cl->setPasswordUsedToConnect("");
    }
    if (cl->getNick() == "UNKNOWN")
    {
        //create client
        std::cout << "CREATING CLIENT GO\n";
        cl->setNick(nickname);
        if (!controller.getServer().isPasswordOk(cl->getPasswordUsedToConnect()))
            quit(controller);
        else
            reply = welcome(nickname, controller.getParser().getArgument());
    }
    else
    {
        //update client
        reply = ":" + cl->getNick() + " NICK " + nickname + "\n";
        cl->setNick(nickname);
    }
    return reply;
}

std::string    nick(const CmdController& controller)
{
    std::string nickname = controller.getParser().getArgument().arg1;
    if (nickname.empty())
        return std::string(ERR_NONICKNAMEGIVEN);

    if (nickname.length() > MAX_NICK_LENGTH)
        return std::string(ERR_ERRONEUSNICKNAME(nickname));

    IrcServer *server = &controller.getServer();
    if (server->isNickInUse(nickname))
        return std::string(ERR_NICKNAMEINUSE(nickname));

    return execNick(controller, nickname);
}
