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
    void insert(int start, int length, uint32_t value);

protected:
    uint8_t buffer[Setting::Signal::BUFFER_LENGTH]{0, 0, 0};
    std::atomic<bool> connectionStatus{false};
    std::mutex mtx;

    virtual void run(void) = 0;

public:
    // Virtual destructor to ensure proper cleanup of derived classes
    virtual ~COMService() = default;

    bool isConnected(void) { return connectionStatus; }

    void setSpeed(uint32_t speed);
    void setTemperature(int32_t temperature);
    void setBatteryLevel(uint32_t batteryLevel);

    void setLeftLightStatus(bool status);
    void setRightLightStatus(bool status);
};

#endif
