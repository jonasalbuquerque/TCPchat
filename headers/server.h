//
// Created by jonasalbuquerque on 09/02/2021.
//

#ifndef TCPCHAT_SERVER_H
#define TCPCHAT_SERVER_H

#include "TcpPacket.h"
#include "sockethandler.h"
#include "utils.h"
#include <algorithm>

class Server {
public:
    Server();

    [[noreturn]] void listen();
private:
    SocketHandler socketHandler_;
    std::shared_ptr<TcpPacket> packet_;
    std::shared_ptr<std::vector<uint8_t>> request_buffer;
    std::shared_ptr<std::vector<int>> usersSockets_;
};

#endif //TCPCHAT_SERVER_H
