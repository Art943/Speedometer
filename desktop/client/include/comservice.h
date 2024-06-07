#ifndef COMSERVICE_H
#define COMSERVICE_H

#include "setting.h"

#include <atomic>
#include <cstdint>
#include <iostream>

class COMService
{
private:
    uint8_t buffer[Setting::Signal::BUFFER_LENGTH];

    virtual void run(void) = 0;

    void extract(int start, int length, uint32_t &value);

public:
    uint32_t extractSpeed();
    int32_t extractTemperature();
    uint32_t extractBatteryLevel();

    bool leftLightStatus();
    bool rightLightStatus();
    bool warningLightStatus();

    virtual uint8_t recieveBuffer() = 0;

    virtual bool isConnected() const = 0;
};

#endif