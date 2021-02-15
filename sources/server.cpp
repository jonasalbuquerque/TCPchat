#include "../headers/server.h"

Server::Server()
{
    socketHandler_.openSocket();
    socketHandler_.bind(SERVER_PORT);
    Server::addClient(socketHandler_.accept());
}

void Server::listen()
{
    std::shared_ptr<std::vector<uint8_t>> request_buffer = std::make_shared<std::vector<uint8_t>>(100,0);
    socketHandler_.recv(request_buffer);
    packet_ = TcpPacket::decode(request_buffer);
    Utils::displayInfo(packet_, "ON SERVER REQUEST");
    Server::reply();
}

void Server::reply()
{
    packet_->setPayload("Client says: "+packet_->getPayload());
    sleep(1);
    socketHandler_.send(packet_->encode());
    Server::listen();
}

void Server::addClient(std::shared_ptr<int> newClientSocket)
{
    clientSockets_.push_back(newClientSocket);
}