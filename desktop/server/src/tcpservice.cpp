#include "tcpservice.h"

TCPService::TCPService()
{
    sockaddr_in servaddr;

    while (true)
    {
        socketID = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
        if (socketID < 0)
        {
            sleep(1); // Wait before retrying
            continue;
        }

        int opt = 1;
        if (setsockopt(socketID, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
        {
            close(socketID);
            sleep(1); // Wait before retrying
            continue;
        }

        servaddr.sin_family = AF_INET;
        servaddr.sin_port = htons(Setting::TCP::PORT);
        servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

        if (bind(socketID, (sockaddr *)&servaddr, sizeof(servaddr)) < 0)
        {
            close(socketID);
            sleep(1); // Wait before retrying
            continue;
        }

        if (listen(socketID, 1) < 0)
        {
            close(socketID);
            sleep(1); // Wait before retrying
            continue;
        }

        // Setup successful
        break;
    }
}

void TCPService::run(void)
{
    sockaddr_in cli;
    socklen_t len = sizeof(cli);

    while (running)
    {
        int connfd = accept(socketID, (sockaddr *)&cli, &len);
        if (connfd < 0)
        {
            // Connection Failed
            std::cout << "Trying to connect to Client..." << std::endl;
            sleep(1);
            continue;
        }

        // Connection successful
        connectionStatus = true;

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

        close(connfd);
    }
}