#include "sockethandler.h"

void SocketHandler::openSocket()
{
    //AF_INET: domain (IPv4); SOCK_STREAM: type (TCP); IPPROTO_IP: ip protocol (value 0)
    if((socketFd_ = ::socket(AF_INET, SOCK_STREAM, IPPROTO_IP)) <= 0)
    {
        throw std::runtime_error("Socket Error");
    }
}

void SocketHandler::bind(const uint16_t &port)
{
    srcAddress_.sin_family = AF_INET;
    srcAddress_.sin_addr.s_addr = INADDR_ANY;
    srcAddress_.sin_port = htons(port);

    if (::bind(socketFd_, (struct sockaddr *) &srcAddress_, sizeof(srcAddress_)) < 0)
    {
        throw std::runtime_error("Bind Error");
    }
}

std::shared_ptr<int> SocketHandler::accept()
{
    socklen_t addrlen = sizeof (destAddress_);
    std::shared_ptr<int> newsockfd = std::make_shared<int>(::accept(socketFd_,
                       (struct sockaddr *) &destAddress_, &addrlen));
    if (newsockfd < 0)
    {
        throw std::runtime_error("Accept Error");
    }
    return newsockfd;
}

void SocketHandler::connect(const uint16_t &port, const std::string &ip)
{
    destAddress_.sin_family = AF_INET;
    destAddress_.sin_addr.s_addr = inet_addr(ip.data());
    destAddress_.sin_port = htons(port);

    if (::connect(socketFd_,
                  (struct sockaddr *) &destAddress_,
                  sizeof (destAddress_)) < 0)
    {
        throw std::runtime_error("Connect Error");
    }
}

void SocketHandler::send(const std::shared_ptr<std::vector<uint8_t>>& buf) const
{
    if (::send(socketFd_, buf->data(), buf->size(),0) < 0)
    {
        throw std::runtime_error("Send Error");
    }
}

void SocketHandler::recv(const std::shared_ptr<std::vector<uint8_t>>& buf) const
{
    if (::recv(socketFd_, buf->data(), buf->size(),0) < 0)
    {
        throw std::runtime_error("Receive Error");
    }
}


