#include "TcpAcceptor.hpp"

TcpAcceptor::TcpAcceptor(){}

TcpAcceptor::TcpAcceptor(int port, std::string address) : _mListenSd(0), _mAddress(address), _mPort(port), _mListening(false) {}

TcpAcceptor::~TcpAcceptor(){
    if (_mListenSd > 0)
        close(_mListenSd);
}

void         TcpAcceptor::init(){
    if (_mListening == true)
        return;
    
    createListenSocket();

    struct sockaddr_in address;
    inetSocketAddress(&address);

    setSocketOptions();
    
    bindSocket(&address);
    
    setSocketListen();
    
    _mListening = true;
}

TcpStream*  TcpAcceptor::accept(){
    if (_mListening == false)
        return NULL;
    struct sockaddr_in address;
    socklen_t length = sizeof(address);
    memset(&address, 0, sizeof(address));

    int sd = ::accept(_mListenSd, (struct sockaddr*)&address, &length);
    if (sd < 0)
        throw std::runtime_error("accept failed");
    return new TcpStream(sd, &address);
}

int         TcpAcceptor::getListenSd() const{
    return _mListenSd;
}

std::string TcpAcceptor::getAddress() const{
    return _mAddress;
}

int         TcpAcceptor::getPort() const{
    return _mPort;
}

bool        TcpAcceptor::isListening() const {
    return _mListening;
}

void        TcpAcceptor::createListenSocket(){
    _mListenSd = socket(AF_INET, SOCK_STREAM, 0);
}

void        TcpAcceptor::inetSocketAddress(struct sockaddr_in *address){
    memset(address, 0, sizeof(*address));
    address->sin_family = AF_INET;
    address->sin_port = htons(_mPort);
    address->sin_addr.s_addr = inet_addr(_mAddress.c_str());
}

void        TcpAcceptor::bindSocket(struct sockaddr_in *address){
    int result = bind(_mListenSd, (struct sockaddr*)address, sizeof(*address));
    if (result != 0)
        throw std::runtime_error("bind failed");
}

void        TcpAcceptor::setSocketListen(){
    int result = listen(_mListenSd, 16);
    if (result != 0)
        throw std::runtime_error("listen failed");
}

void        TcpAcceptor::setSocketOptions(){
    //makes it possible to immidetly listen on same adddress and port when restart server
    int optval = 1;
    setsockopt(_mListenSd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
}

std::ostream&           operator<<(std::ostream& o, TcpAcceptor const& src){
    o << "Listen FD = " << src.getListenSd();
    return o;
}
