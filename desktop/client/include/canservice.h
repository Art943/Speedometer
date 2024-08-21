#ifndef CANCOM_H
#define CANCOM_H

#include "comservice.h"

#include <atomic>
#include <iostream>
#include <QThread>
#include <QSerialPort>

class CANService : public COMService, public QThread
{
    std::atomic<bool> running{true};

    void run(void) override;

public:
    CANService()
    {
        start();
    }
    ~CANService()
    {
        running = false;
        connectionStatus = false;
        wait();
    }
};

#endif