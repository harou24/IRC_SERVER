#include "multi_client_handler.hpp"

MultiClientHandler::MultiClientHandler(void)
{
    this->zeroFdSet();
    this->fdMax_ = 0;
    timer_.tv_sec = 0;
    timer_.tv_usec = 500;
}

MultiClientHandler::~MultiClientHandler(void) { }

void    MultiClientHandler::zeroFdSet(void)
{
    FD_ZERO(&this->mainFds_);
    FD_ZERO(&this->tmpFds_);
}

void    MultiClientHandler::addFdToSet(int fd)
{
    FD_SET(fd, &this->mainFds_);
    if (size_t(fd) > fdMax_)
        this->fdMax_ = fd;
}

void    MultiClientHandler::clearFd(int fd)
{
    FD_CLR(fd, &this->mainFds_);
}

bool    MultiClientHandler::isFdInSet(int fd)
{
    this->updateFdSet();
    return (FD_ISSET(fd, &this->tmpFds_) != 0);
}

void    MultiClientHandler::updateFdSet(void)
{
    this->tmpFds_ = this->mainFds_;
    if (select(this->fdMax_ + 1, &this->tmpFds_, NULL, NULL, &timer_) == - 1)
        throw std::runtime_error("select " + std::string(strerror(errno)));
}

bool    MultiClientHandler::isFdReadyToCommunicate(int fd)
{
    return this->isFdInSet(fd);
}

size_t  MultiClientHandler::getFdmax() const
{
    return fdMax_;
}

std::ostream&   operator<<(std::ostream& o, MultiClientHandler const& src)
{
    o << "fdmax = " << src.getFdmax();
    return o;
}
