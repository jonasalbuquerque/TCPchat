#include "../headers/server.h"

#undef max
#define max(x,y) ((x) > (y) ? (x) : (y))

Server::Server() : request_buffer(new std::vector<uint8_t>(200,0)),
                    usersSockets_(new std::vector<int>(5,0))
{
    socketHandler_.openSocket();
    socketHandler_.bind(SERVER_PORT);
    socketHandler_.listen();
}

[[noreturn]] void Server::listen()
{
    while (true)
    {
        int ready, nfds = 0;
        int host = socketHandler_.getSocket();
        fd_set readfds;
        FD_ZERO(&readfds);
        FD_SET(host, &readfds);
        nfds = max(nfds, host);
        for (const auto& user : *usersSockets_)
        {
            if (user>0) FD_SET(user, &readfds);
            nfds = max(nfds, user);
        }
        ready = select(nfds + 1, &readfds, NULL, NULL, NULL);

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
            if(FD_ISSET(user, &readfds))
            {
                std::fill(request_buffer->begin(), request_buffer->end(), 0);
                socketHandler_.recvAll(request_buffer, usersSockets_);
                packet_ = TcpPacket::decode(request_buffer);
                if (packet_->getPayload() == "/SAIR")
                {
                    usersSockets_->erase(std::remove(usersSockets_->begin(), usersSockets_->end(), user), usersSockets_->end());
                }
                else
                {
                    std::cout << "ON SERVER: " << packet_->getPayload() << std::endl;
                }
            }
        }
    }
}