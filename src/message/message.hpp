#ifndef MESSAGE_HPP
# define MESSAGE_HPP

#include "tcp_stream.hpp"

class Message {

    public:
        Message();
        Message(const std::string& data, TcpStream *stream);
        ~Message();

        std::string getData() const;
        TcpStream&  getStream() const;
        TcpStream*  getStreamPtr();

    private:
        std::string data_;
        TcpStream*  stream_;
};

#endif