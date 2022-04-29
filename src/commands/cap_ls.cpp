#include "commands.hpp"

std::string    cap_ls(CmdController* controller)
{
    if (controller)
        std::cout << "CAP LS cmd!\n";
    return std::string("Reply\n");
}
