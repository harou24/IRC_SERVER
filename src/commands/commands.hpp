#ifndef COMMANDS_HPP
# define COMMANDS_HPP

# include "cmd_controller.hpp"
# include "command_type.hpp"
# include "replies.hpp"
# include <string>

struct Args;
class CmdController;

std::string    welcome(std::string nick, Args& args);
std::string    cap_ls(const CmdController& controller);
std::string    nick(const CmdController& controller);
std::string    user(const CmdController& controller);
std::string    ping(const CmdController& controller);
std::string    mode(const CmdController& controller);
std::string    cap_ls(const CmdController& controller);
std::string    unknown(const CmdController& controller);
std::string    pong(const CmdController& controller);
std::string    privmsg(const CmdController& controller);
std::string    mode(const CmdController& controller);
std::string    quit(const CmdController& controller);
std::string    away(const CmdController& controller);
std::string    join(const CmdController& controller);
std::string    invite(const CmdController& controller);
std::string    part(const CmdController& controller);
std::string    kick(const CmdController& controller);
std::string    pass(const CmdController& controller);
std::string    topic(const CmdController& controller);
std::string    notice(const CmdController& controller);

std::string    generateRandom(const int len);


#endif