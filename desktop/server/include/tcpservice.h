#ifndef TCPCOM_H
#define TCPCOM_H

#include "comservice.h"

#include <thread>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

class TCPService : public COMService
{
    int socketID{0};
    std::atomic<bool> running{true};
    std::thread thrd{&TCPService::run, this};

    void run(void) override;

public:
    TCPService();
    ~TCPService()
    {
        running = false;
        connectionStatus = false;
        shutdown(socketID, SHUT_RDWR);
        close(socketID);
        thrd.join();
    }
};

#endif