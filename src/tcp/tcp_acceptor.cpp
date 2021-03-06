#include "tcp_acceptor.hpp"

TcpAcceptor::TcpAcceptor(){}

TcpAcceptor::TcpAcceptor(int port, std::string address) : listenSd_(0), address_(address), port_(port), listening_(false) {}

TcpAcceptor::~TcpAcceptor()
{
    if (listenSd_ > 0)
        close(listenSd_);
}

int         TcpAcceptor::init()
{
    if (listening_ == true)
        return 0;
    
    createListenSocket();

    struct sockaddr_in address;
    inetSocketAddress(&address);

    setSocketOptions();
    
    int result = bindSocket(&address);
    
    result = setSocketListen();
    
    listening_ = true;
    return result;
}

TcpStream*  TcpAcceptor::accept()
{
    if (listening_ == false)
        return NULL;
    struct sockaddr_in address;
    socklen_t length = sizeof(address);
    memset(&address, 0, sizeof(address));

    int sd = ::accept(listenSd_, (struct sockaddr*)&address, &length);
    if (sd < 0)
        throw std::runtime_error("accept " + std::string(strerror(errno)));
    return new TcpStream(sd, &address);
}

int         TcpAcceptor::getListenSd() const
{
    return listenSd_;
}

void        TcpAcceptor::createListenSocket()
{
    listenSd_ = socket(AF_INET, SOCK_STREAM, 0);
}

void        TcpAcceptor::inetSocketAddress(struct sockaddr_in *address)
{
    memset(address, 0, sizeof(*address));
    address->sin_family = AF_INET;
    address->sin_port = htons(port_);
    address->sin_addr.s_addr = INADDR_ANY;
}

int         TcpAcceptor::bindSocket(struct sockaddr_in *address)
{
    int result = bind(listenSd_, (struct sockaddr*)address, sizeof(*address));
    if (result != 0)
        throw std::runtime_error("bind " + std::string(strerror(errno)));
    return result;
}

int         TcpAcceptor::setSocketListen()
{
    int result = listen(listenSd_, 16);
    if (result != 0)
        throw std::runtime_error("listen " + std::string(strerror(errno)));
    return result;
}

void        TcpAcceptor::setSocketOptions()
{
    //makes it possible to immidetly listen on same adddress and port when restart server
    int optval = 1;
    setsockopt(listenSd_, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof optval);
}

std::ostream&           operator<<(std::ostream& o, TcpAcceptor const& src)
{
    o << "Listen FD = " << src.getListenSd();
    return o;
}
