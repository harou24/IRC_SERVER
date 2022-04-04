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
    if (size_t(fd) > fdMax)
        this->fdMax = fd;
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
    timeval T;
    T.tv_sec = 0; T.tv_usec = 500;
    this->tmpFds = this->mainFds;
    if (select(this->fdMax + 1, &this->tmpFds, NULL, NULL, &T) == - 1)
        throw UpdateFailed();
}

bool    MultiClientHandler::isFdReadyToCommunicate(int fd)
{
    return this->isFdInSet(fd);
}

size_t  MultiClientHandler::getFdmax() const{
    return fdMax;
}

const char* MultiClientHandler::UpdateFailed::what() const throw()
{
    return ("Error : Tcp connection error @_@");
}

std::ostream&   operator<<(std::ostream& o, MultiClientHandler const& src){
    o << "fdmax = " << src.getFdmax();
    return o;
}
