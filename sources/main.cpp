#include <thread>

#include "../headers/client.h"
#include "../headers/server.h"

void start_server()
{
    try
    {
        Server server;
        server.start();
    }
    catch (const std::exception& e)
    {
        std::string error_msg = "ON SERVER: ";
        error_msg.append(e.what());
        throw std::runtime_error(error_msg);
    }
}

void start_client(uint16_t port)
{
    try
    {
        Client client(port);
        client.send();
    }
    catch (const std::exception& e)
    {
        std::string error_msg = "ON CLIENT: ";
        error_msg.append(e.what());
        throw std::runtime_error(error_msg);
    }
}

int main()
{
    try
    {
        std::thread th_server (start_server);
        std::thread th_client (start_client, 5001);
//        std::thread th_client2 (start_client, 5002);

        th_server.join();
        th_client.join();
//        th_client2.join();

        return 0;
    }
    catch(const std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}
