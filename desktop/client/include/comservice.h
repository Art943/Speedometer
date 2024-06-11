#ifndef COMSERVICE_H
#define COMSERVICE_H

#include "setting.h"

#include <atomic>
#include <cstdint>
#include <cstddef>
#include <mutex>

class COMService
{
private:
    void extract(int start, int length, uint32_t &value);

protected:
    uint8_t buffer[Setting::Signal::BUFFER_LENGTH];
    std::mutex mtx;
    std::atomic<bool> connected;

    virtual void run(void) = 0;

public:
    // Virtual destructor to ensure proper cleanup of derived classes
    virtual ~COMService() {}

    uint32_t getSpeed();
    int32_t getTemperature();
    uint32_t getBatteryLevel();

    bool leftLightStatus();
    bool rightLightStatus();
    bool warningLightStatus();
};

#endif