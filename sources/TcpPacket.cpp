#include "../headers/TcpPacket.h"

#include <utility>

TcpPacket::TcpPacket() = default;

TcpPacket::TcpPacket(std::string p_payload) : payload_{std::move(p_payload)}{}

std::shared_ptr<std::vector<uint8_t>> TcpPacket::encode()
{
    std::shared_ptr<std::vector<uint8_t>> pckt = std::make_shared<std::vector<uint8_t>>();
    for (const auto& c : payload_)
    {
        pckt->push_back(static_cast<uint8_t> (c));
    }
    return pckt;
}
std::shared_ptr<TcpPacket> TcpPacket::decode(const std::shared_ptr<std::vector<uint8_t>> &inputPacket)
{
    std::shared_ptr<TcpPacket> pckt = std::make_shared<TcpPacket>();
    std::string payload_msg;
    for (int i = 8; i < inputPacket->size(); ++i){
        payload_msg.push_back(inputPacket->at(i));
    }
    pckt->setPayload(payload_msg);
    return pckt;
}

std::string TcpPacket::getPayload() const  {return payload_;}

void TcpPacket::setPayload(const std::string &newPayload) { payload_ = newPayload; }

