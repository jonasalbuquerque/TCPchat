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
        th_server.join();
        while (true)
        {
            uint8_t counter = 1;
            std::cout << "Welcome to chat\n" <<
                      "Enter a command: "    <<
                      "1. /ENTRAR\n"         <<
                      "2. /USUARIOS\n"       <<
                      "3. /SAIR\n"           <<
                      "or type a message"    << std::endl;
            std::string entry;
            std::cin >> entry;
            if(entry == "/ENTRAR")
            {
                std::thread th_client (start_client, 5000 + counter++);
                th_client.join();
            }
            else if (entry == "/USUARIOS")
            {
                continue;
            }
            else
            {
                std::string user;
                std::cout << "Enter the nickname: ";
                getline(std::cin, user);
                //thread = get_thread_by_nickname
                if (entry == "/SAIR")
                {
                    //call_server_to_remove_client(thread)
                    continue;
                }
                else
                {
                    //thread.send_to_server(entry)
                }
            }
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    return 0;
}
