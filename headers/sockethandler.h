#ifndef TCPCHAT_SOCKETHANDLER_H
#define TCPCHAT_SOCKETHANDLER_H

#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/select.h>
#include <memory>
#include <stdexcept>
#include <vector>
#include <iostream>

#define SERVER_PORT 5000

class SocketHandler {
private:
    int socketFd_;
    sockaddr_in srcAddress_, destAddress_;
public:
    void openSocket();
    void bind(const uint16_t &port);
    void connect(const uint16_t &port,
                 const std::string &ip);
    void listen() const;
    void accept(const std::shared_ptr<std::vector<int>>& usersList);
    void sendAll(const std::shared_ptr<std::vector<uint8_t>>& buf) const;
    void recvAll(const std::shared_ptr<std::vector<uint8_t>>& buf, const std::shared_ptr<std::vector<int>>& usersList) const;
    void send(const std::shared_ptr<std::vector<uint8_t>>& buf) const;
    void recv(const std::shared_ptr<std::vector<uint8_t>>& buf) const;

    int getSocket();
};

#endif //TCPCHAT_SOCKETHANDLER_H
