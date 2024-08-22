#include "tcpservice.h"

void TCPService::run(void)
{
    int socketID;
    sockaddr_in servaddr;

    // Assign IP and PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(Setting::TCP::PORT);
    servaddr.sin_addr.s_addr = inet_addr(Setting::TCP::IP);

    while (running)
    {
        socketID = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);

        if (0 != ::connect(socketID, (sockaddr *)&servaddr, sizeof(servaddr)))
        {
            close(socketID);
            socketID = -1;
            std::cout << "Trying to connect to server..." << std::endl;
            QThread::sleep(1);
            continue;
        }

        if (socketID > -1)
        {
            connectionStatus = true;

            while (connectionStatus)
            {
                uint8_t temp_buffer[Setting::Signal::BUFFER_LENGTH];

                // Receive data from the server and store it in buffer
                if (Setting::Signal::BUFFER_LENGTH != read(socketID, temp_buffer, Setting::Signal::BUFFER_LENGTH))
                {
                    connectionStatus = false;
                    break;
                }

                mtx.lock();
                memcpy(buffer, temp_buffer, Setting::Signal::BUFFER_LENGTH);
                mtx.unlock();

                QThread::msleep(20);
            }

            close(socketID);
        }
    }
}
