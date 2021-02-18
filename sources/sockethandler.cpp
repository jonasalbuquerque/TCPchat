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

void SocketHandler::listen() const
{
    std::cout << "Listening on port: " << ntohs(srcAddress_.sin_port) << std::endl;
    ::listen(socketFd_,1);
}

void SocketHandler::accept(const std::shared_ptr<std::vector<int>>& usersList)
{
    socklen_t addrlen = sizeof (destAddress_);
    int newsockfd = ::accept(socketFd_,
                       (struct sockaddr *) &destAddress_, &addrlen);
    if (socketFd_ < 0)
    {
        throw std::runtime_error("Accept Error");
    }
    usersList->push_back(newsockfd);
    std::cout << "New connection from port " << ntohs(destAddress_.sin_port) << std::endl;
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

void SocketHandler::broadcast(const std::shared_ptr<std::vector<uint8_t>>& buf, const std::shared_ptr<std::vector<int>> &usersList)
{
    for (const auto& user : *usersList)
    {
        if (::send(user, buf->data(), buf->size(),0) < 0)
        {
            throw std::runtime_error("Broadcast Error");
        }
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

void SocketHandler::recvfrom(const int &sckt, const std::shared_ptr<std::vector<uint8_t>> &buf)
{
    if (::recv(sckt, buf->data(), buf->size(),0) < 0)
    {
        throw std::runtime_error("ReceiveFrom Error");
    }
}

int SocketHandler::getSocket() const { return socketFd_; }


