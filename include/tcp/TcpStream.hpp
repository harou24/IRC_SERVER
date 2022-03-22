#include <sys/socket.h>
#include <string>

class TcpStream
{
    public:
        ~TcpStream();

        std::string     getPeerIP();
        int             getPeerPort();

    private:
        int             _mSd;
        std::string     _mPeerIP;
        int             _mPeerPort;

    private:
        TcpStream();
        TcpStream(int sd, struct sockaddr_in* address);
        TcpStream(const TcpStream& src);

}