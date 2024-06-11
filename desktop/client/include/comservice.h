#ifndef COMSERVICE_H
#define COMSERVICE_H

#include "setting.h"

#include <atomic>
#include <cstddef>
#include <cstdint>
#include <mutex>

class COMService
{
private:
    void extract(int start, int length);

protected:
    uint8_t buffer[Setting::Signal::BUFFER_LENGTH];
    std::atomic<bool> status{false};
    std::mutex mtx;

    virtual void run(void) = 0;

public:
    // Virtual destructor to ensure proper cleanup of derived classes
    virtual ~COMService() = default;

    bool connected(void) { return status; }

    uint32_t getSpeed();
    int32_t getTemperature();
    uint32_t getBatteryLevel();

    bool leftLightStatus();
    bool rightLightStatus();
    bool warningLightStatus();
};

#endif