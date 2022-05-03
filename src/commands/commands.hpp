#ifndef COMMANDS_HPP
# define COMMANDS_HPP

# include "cmd_controller.hpp"
# include "command_type.hpp"
# include "replies.hpp"
# include <string>

struct Args;
class CmdController;

std::string    welcome(std::string nick, Args& args);
std::string    cap_ls(CmdController* controller);
std::string    nick(CmdController* controller);
std::string    user(CmdController* controller);
std::string    ping(CmdController* controller);
std::string    mode(CmdController* controller);
std::string    cap_ls(CmdController* controller);
std::string    unknown(CmdController* controller);
std::string    pong(CmdController* controller);
std::string    privmsg(CmdController* controller);
std::string    mode(CmdController* controller);


#endif