#include "tcpservice.h"

void TCPService::run(void)
{

    socketID = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
    if (socketID == -1)
    {
        std::cout << "Failed to create the socket..." << std::endl;
        std::exit(EXIT_FAILURE);
    }

    sockaddr_in servaddr;

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(Setting::TCP::PORT);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (0 != bind(socketID, (sockaddr *)&servaddr, sizeof(servaddr)))
    {
        close(socketID);
        std::cout << "Failed to bind servaddr to the socket..." << std::endl;
        std::exit(EXIT_FAILURE);
    }

    if (0 != listen(socketID, 1))
    {
        close(socketID);
        std::cout << "Failed to listen to the port..." << std::endl;
        std::exit(EXIT_FAILURE);
    }

    sockaddr_in cli;
    socklen_t len = sizeof(cli);

    while (running)
    {

        int connfd = accept(socketID, (sockaddr *)&cli, &len);
        if (connfd < 0)
        {
            // Connection Failed
            close(socketID);
            std::cout << "Connection to the client failed..." << std::endl;
            std::exit(EXIT_FAILURE);
        }
        else
        {
            // Connection successful
            connectionStatus = true;
        }

        while (isConnected())
        {
            uint8_t temp_buffer[Setting::Signal::BUFFER_LENGTH];

            mtx.lock();
            memcpy(temp_buffer, buffer, Setting::Signal::BUFFER_LENGTH);
            mtx.unlock();

            if (Setting::Signal::BUFFER_LENGTH != write(connfd, temp_buffer, Setting::Signal::BUFFER_LENGTH))
            {
                shutdown(connfd, SHUT_RDWR);
                close(connfd);
                connectionStatus = false;
                break;
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(20));
        }
    }
}