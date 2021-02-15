#ifndef TCPCHAT_CLIENT_H
#define TCPCHAT_CLIENT_H

#include "TcpPacket.h"
#include "sockethandler.h"
#include "utils.h"

class Client {
public:
    Client();
    [[noreturn]] void send();
    void receive();
private:
    SocketHandler socketHandler_;
    std::shared_ptr<TcpPacket> packet_;
    std::shared_ptr<std::vector<uint8_t>> reply_buffer;
};

#endif //TCPCHAT_CLIENT_H
