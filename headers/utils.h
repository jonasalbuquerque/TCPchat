#ifndef TCPCHAT_UTILS_H
#define TCPCHAT_UTILS_H

#include <iostream>
#include <memory>
#include "TcpPacket.h"

class Utils {
public:
    static void displayInfo(std::shared_ptr<TcpPacket> packet, std::string extra_msg);
    static std::string recursiveParser(std::string expressionToParse);
};


#endif //TCPCHAT_UTILS_H
