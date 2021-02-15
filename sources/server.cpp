#include "../headers/server.h"

Server::Server() : request_buffer(new std::vector<uint8_t>(100,0))
{
    socketHandler_.openSocket();
    socketHandler_.bind(SERVER_PORT);
    socketHandler_.accept();
}

void Server::listen()
{
    socketHandler_.recv(request_buffer);
    packet_ = TcpPacket::decode(request_buffer);
    Utils::displayInfo(packet_, "ON SERVER REQUEST ");
    Server::reply();
}

void Server::reply()
{
    sleep(1);
    packet_->setPayload("Client says: "+packet_->getPayload());
    socketHandler_.send(packet_->encode());
    Server::listen();
}