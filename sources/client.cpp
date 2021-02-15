#include "../headers/client.h"

Client::Client()
{
    socketHandler_.openSocket();
    socketHandler_.bind(CLIENT_PORT);
    socketHandler_.connect(SERVER_PORT, "127.0.0.1");
}

[[noreturn]] void Client::send()
{
    packet_ = std::make_shared<TcpPacket> ();
    while(true)
    {
        std::string msg;
        std::cout << "Insert a message: ";
        getline(std::cin, msg);
        packet_->setPayload(msg);
        sleep(1);
        socketHandler_.send(packet_->encode());
        Client::receive();
    }
}

void Client::receive()
{
    std::shared_ptr<std::vector<uint8_t>> reply_buffer = std::make_shared<std::vector<uint8_t>>(50,0);
    socketHandler_.recv(reply_buffer);
    packet_ = TcpPacket::decode(reply_buffer);
    Utils::displayInfo(packet_, "ON CLIENT RESPONSE  ");
}