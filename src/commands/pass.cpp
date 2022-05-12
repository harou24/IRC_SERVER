#include "commands.hpp"

std::string    pass(const CmdController& controller)
{
    std::string reply("");
    std::string password = controller.getParser().getArgument().arg1;

    if (!controller.getServer().isPasswordOk(password))
    {
        reply = ":Password incorrect";
        std::cout << "---------PASSS INCORRECT-------------\n";
    }
    return reply;
}