#ifndef TCPCHAT_CLIENT_H
#define TCPCHAT_CLIENT_H

#include "TcpPacket.h"
#include "sockethandler.h"
#include "utils.h"

class Client {
public:
    Client(uint16_t port);
    void send();
    void receive();
private:
    uint16_t port_;
    SocketHandler socketHandler_;
    std::shared_ptr<TcpPacket> packet_;
    std::shared_ptr<std::vector<uint8_t>> reply_buffer;
};

#endif //TCPCHAT_CLIENT_H
