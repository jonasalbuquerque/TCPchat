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
    void addClient(std::shared_ptr<int> newClientSocket);
private:
    SocketHandler socketHandler_;
    std::shared_ptr<TcpPacket> packet_;
    std::vector<std::shared_ptr<int>> clientSockets_;
};

#endif //TCPCHAT_SERVER_H
