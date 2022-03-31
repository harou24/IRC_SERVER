#include "IrcServer.hpp"

        IrcServer::IrcServer(int port, std::string password) : _mServer(port, password) {}
