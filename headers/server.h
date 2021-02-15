//
// Created by jonasalbuquerque on 09/02/2021.
//

#ifndef TCPCHAT_SERVER_H
#define TCPCHAT_SERVER_H

#include "TcpPacket.h"
#include "sockethandler.h"
#include "utils.h"

class Server {
public:
    Server();
    void listen();
    void reply();
private:
    SocketHandler socketHandler_;
    std::shared_ptr<TcpPacket> packet_;
    std::shared_ptr<std::vector<uint8_t>> request_buffer;
};

#endif //TCPCHAT_SERVER_H
