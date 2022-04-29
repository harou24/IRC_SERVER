#ifndef COMMANDS_HPP
# define COMMANDS_HPP

# include "cmd_controller.hpp"
# include "command_type.hpp"
# include <string>

class CmdController;

std::string    welcome();
std::string    cap_ls(CmdController* controller);
std::string    nick(CmdController* controller);
std::string    user(CmdController* controller);
std::string    ping(CmdController* controller);
std::string    mode(CmdController* controller);
std::string    cap_ls(CmdController* controller);
std::string    unknown(CmdController* controller);

#endif