#include <utils.h>

void Utils::displayInfo(std::shared_ptr <TcpPacket> packet, std::string extra_msg)
{
    std::cout   << extra_msg
                << " payload=\""    << packet->getPayload()  << "\""
                << std::endl;
}