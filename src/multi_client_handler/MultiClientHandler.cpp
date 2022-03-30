#include "MultiClientHandler.hpp"

MultiClientHandler::MultiClientHandler(void)
{
    this->zeroFdSet();
    this->fdMax = 0;
}

MultiClientHandler::~MultiClientHandler(void) { }

void    MultiClientHandler::zeroFdSet(void)
{
    FD_ZERO(&this->mainFds);
    FD_ZERO(&this->tmpFds);
}

void    MultiClientHandler::addFdToSet(int fd)
{
    FD_SET(fd, &this->mainFds);
    this->fdMax += 1;
}

void    MultiClientHandler::clearFd(int fd)
{
    FD_CLR(fd, &this->mainFds);
}

bool    MultiClientHandler::isFdInSet(int fd)
{
    this->updateFdSet();
    return (FD_ISSET(fd, &this->tmpFds) != 0);
}


void    MultiClientHandler::updateFdSet(void)
{
    this->tmpFds = this->mainFds;
    if (select(this->fdMax + 1, &this->tmpFds, NULL, NULL, NULL) == - 1)
        throw new UpdateFailed();
}

bool    MultiClientHandler::isFdReadyToCommunicate(int fd)
{
    return this->isFdInSet(fd);
}

const char* MultiClientHandler::UpdateFailed::what() const throw()
{
    return ("Error : Tcp connection error @_@");
}