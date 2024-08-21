#ifndef TCPCOM_H
#define TCPCOM_H

#include "comservice.h"

#include <cstring>
#include <iostream>
#include <unistd.h>
#include <QThread>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

class TCPService : public COMService, public QThread
{
    std::atomic<bool> running{true};

    void run(void) override;

public:
    TCPService()
    {
        start();
    }

    ~TCPService()
    {
        running = false;
        connectionStatus = false;
        wait();
    }
};

#endif