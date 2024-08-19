#ifndef CANCOM_H
#define CANCOM_H

#include "comservice.h"

#include <atomic>
#include <iostream>
#include <thread>
#include <QSerialPort>

class CANService : public COMService
{
    std::atomic<bool> running{true};
    std::thread thrd{&CANService::run, this};

    void run(void) override;

public:
    ~CANService()
    {
        running = false;
        connectionStatus = false;
        thrd.join();
    }
};

#endif