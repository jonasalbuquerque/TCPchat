#include "../headers/client.h"

Client::Client() : reply_buffer(new std::vector<uint8_t> (100,0))
{
    socketHandler_.openSocket();
    socketHandler_.bind(CLIENT_PORT);
    socketHandler_.connect(SERVER_PORT, "127.0.0.1");
}

[[noreturn]] void Client::send()
{
    packet_ = std::make_shared<TcpPacket> ();
    while (true)
    {
        sleep(1);
        std::string msg;
        std::cout << "Insert a message: ";
        getline(std::cin, msg);
        packet_->setPayload(msg);
        socketHandler_.send(packet_->encode());
        Client::receive();
    }
}

void Client::receive()
{
    sleep(1);
    std::fill(reply_buffer->begin(), reply_buffer->end(), 0);
    socketHandler_.recv(reply_buffer);
    packet_ = TcpPacket::decode(reply_buffer);
    Utils::displayInfo(packet_, "ON CLIENT RESPONSE");
}