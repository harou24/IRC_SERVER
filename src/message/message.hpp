#ifndef MESSAGE_HPP
# define MESSAGE_HPP

#include "tcp_stream.hpp"

class Message {
    private:
        std::string data_;
        TcpStream *stream_;

    public:
        Message();
        Message(const std::string& data, TcpStream *stream);
        ~Message();

        std::string getData() const;
        TcpStream&  getStream() const;

};

#endif