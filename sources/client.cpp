#include "../headers/client.h"

Client::Client(uint16_t port) : port_(port),
                                reply_buffer(new std::vector<uint8_t> (200,0))
{
    socketHandler_.openSocket();
    socketHandler_.bind(port_);
    sleep(1);
    socketHandler_.connect(SERVER_PORT, "127.0.0.1");
}

[[noreturn]] void Client::send()
{
    packet_ = std::make_shared<TcpPacket> ();
    std::string msg("User"+std::to_string(port_)+" says: ");
    std::cout << "Insert a message: ";
    getline(std::cin, msg);
    packet_->setPayload(msg);
    socketHandler_.send(packet_->encode());
}

void Client::receive()
{
    std::fill(reply_buffer->begin(), reply_buffer->end(), 0);
    socketHandler_.recv(reply_buffer);
    packet_ = TcpPacket::decode(reply_buffer);
    Utils::displayInfo(packet_, "ON User"+std::to_string(port_));
}