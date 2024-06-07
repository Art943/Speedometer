#ifndef COMSERVICE_H
#define COMSERVICE_H

#include "setting.h"

#include <cstdint>
#include <atomic>

class COMService
{
private:
    uint8_t buffer[Setting::Signal::BUFFER_LENGTH];

    virtual void run(void) = 0;

    void extract(int start, int length, int &value);

public:
    uint32_t extractSpeed();
    uint32_t extractTemperature();
    uint32_t extractBatteryLevel();

    bool leftLightStatus();
    bool rightLightStatus();
    bool communicationStatus();

    uint8_t recieveBuffer();
};

#endif