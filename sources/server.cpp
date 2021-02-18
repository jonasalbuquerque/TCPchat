#include "../headers/server.h"

#undef max
#define max(x,y) ((x) > (y) ? (x) : (y))

Server::Server() : request_buffer(new std::vector<uint8_t>(200,0)),
                    usersSockets_(new std::vector<int>(5,0)),
                    socketHandler_()
{
    socketHandler_.openSocket();
    socketHandler_.bind(SERVER_PORT);
    socketHandler_.listen();
}

[[noreturn]] void Server::start()
{
    while (true)
    {
        int ready, nfds = 0;
        int host = socketHandler_.getSocket();
        fd_set readfds, writefds;
        FD_ZERO(&readfds);
        FD_ZERO(&writefds);
        FD_SET(host, &readfds);
        nfds = max(nfds, host);
        for (const auto& user : *usersSockets_)
        {
            if (user>0)
            {
                FD_SET(user, &readfds);
                FD_SET(user, &writefds);
            }
            nfds = max(nfds, user);
        }
        ready = select(nfds + 1, &readfds, &writefds, nullptr, nullptr);

        if (ready == -1 && errno == EINTR)
            continue;

        if (ready == -1) {
            throw std::runtime_error("Select Error");
        }

        if (FD_ISSET(host, &readfds))
        {
            socketHandler_.accept(usersSockets_);
        }

        for (const auto& user : *usersSockets_)
        {
            if(FD_ISSET(user, &readfds) && FD_ISSET(user, &writefds))
            {
                std::fill(request_buffer->begin(), request_buffer->end(), 0);
                SocketHandler::recvfrom(user, request_buffer);
                if (!request_buffer->empty())
                {
                    packet_ = TcpPacket::decode(request_buffer);
                    if (packet_->getPayload() == "/ENTRAR")
                    {
                        packet_->setPayload("New user connected to chat");
                        SocketHandler::broadcast(packet_->encode(), usersSockets_);
                        break;
                    }
                    else if (packet_->getPayload() == "/SAIR")
                    {
                        usersSockets_->erase(std::remove(usersSockets_->begin(), usersSockets_->end(), user),
                                             usersSockets_->end());
                        break;
                    }
                    else
                    {
                        SocketHandler::broadcast(packet_->encode(), usersSockets_);
                        break;
                    }
                }
            }
        }
    }
}