#include "TcpAcceptor.hpp"

TcpAcceptor::TcpAcceptor(){}

TcpAcceptor::TcpAcceptor(int port, std::string address) : _mLsd(0), _mAddress(address), _mPort(port), _mListening(false) {}

TcpAcceptor::~TcpAcceptor(){
    if (_mLsd > 0)
        close(_mLsd);
}

int         TcpAcceptor::start(){
    if (_mListening == true)
        return 0;
    setLsd();
    struct sockaddr_in address;
    inetSocketAddress(&address);

    //makes it possible to immidetly listen on same adddress and port when restart server
    int optval = 1;
    setsockopt(_mLsd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof optval);

    //bind name to socket
    int result = bind(_mLsd, (struct sockaddr*)&address, sizeof(address));
    if (result != 0)
        throw std::runtime_error("bind failed");
    
    result = listen(_mLsd, 16);
    if (result != 0)
        throw std::runtime_error("listen failed");
    _mListening = true;
    return result;
}

TcpStream*  TcpAcceptor::accept(){
    if (_mListening == false)
        return NULL;
    struct sockaddr_in address;
    socklen_t length = sizeof(address);
    memset(&address, 0, sizeof(address));

    int sd = ::accept(_mLsd, (struct sockaddr*)&address, &length);
    if (sd < 0)
        throw std::runtime_error("accept failed");
    return new TcpStream(sd, &address);
}

void        TcpAcceptor::setLsd(){
    _mLsd = socket(AF_INET, SOCK_STREAM, 0);
}

void        TcpAcceptor::inetSocketAddress(struct sockaddr_in *address){
    memset(address, 0, sizeof(*address));
    address->sin_family = AF_INET;
    address->sin_port = htons(_mPort);

    //set IP address to byte order if address is set otherwise address is set to listen to all
    if(_mAddress.size() > 0)
        address->sin_addr.s_addr = inet_addr(_mAddress.c_str());
    else
        address->sin_addr.s_addr = INADDR_ANY;
}