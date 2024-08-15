#include "tcpservice.h"

void TCPService::run(void)
{
    sockaddr_in servaddr;

    // Assign IP and PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(Setting::TCP::PORT);
    servaddr.sin_addr.s_addr = inet_addr(Setting::TCP::IP);

    while (running)
    {
        socketID = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);

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

                std::this_thread::sleep_for(std::chrono::milliseconds(20));
            }

            close(socketID);
        }
    }
}
