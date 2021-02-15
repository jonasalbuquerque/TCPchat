#ifndef TCPCHAT_TCPPACKET_H
#define TCPCHAT_TCPPACKET_H

#include <iostream>
#include <vector>
#include <unistd.h>
#include <memory>

class TcpPacket {
private:
    std::string payload_;
public:
    TcpPacket();
    TcpPacket(std::string p_payload);
    std::shared_ptr<std::vector<uint8_t>> encode();
    static std::shared_ptr<TcpPacket>     decode(const std::shared_ptr<std::vector<uint8_t>> &inputPacket);
    std::string                           getPayload() const;
    void                                  setPayload(const std::string &newPayload);
};

#endif //TCPCHAT_TCPPACKET_H
