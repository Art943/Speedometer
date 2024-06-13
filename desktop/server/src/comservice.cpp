#include <climits>
#include "comservice.h"

void COMService::insert(int start, int length, uint32_t value)
{
    // Variable to start at the first relevant byte
    uint8_t bufferIndex{start / CHAR_BIT};

    // Variable to start at the first relevant bit
    uint8_t bitOffset{start % CHAR_BIT};

    // Variable to keep track of how many bits we've cleared/inserted
    uint8_t insertedBits{0};

    mtx.lock();

    // Clear the existing data from the buffer
    while (insertedBits < length)
    {
        /* code */
    }

    bufferIndex = start / CHAR_BIT;
    bitOffset = start % CHAR_BIT;
    insertedBits = 0;

    // Insert the relevant data into the buffer
    while (insertedBits < length)
    {
        /* code */
    }
    mtx.unlock();
}

void COMService::setSpeed(uint32_t speed)
{

    insert(Setting::Signal::Speed::Start, Setting::Signal::Speed::Length, speed);
}

void COMService::setTemperature(int32_t temperature)
{
    insert(Setting::Signal::Temperature::Start, Setting::Signal::Temperature::Length, temperature);
}

void COMService::setBatteryLevel(uint32_t batteryLevel)
{
    insert(Setting::Signal::BatteryLevel::Start, Setting::Signal::BatteryLevel::Length, batteryLevel);
}

void COMService::setLeftLightStatus(bool leftLight)
{
    insert(Setting::Signal::LeftLight::Start, Setting::Signal::LeftLight::Length, leftLight);
}

void COMService::setRightLightStatus(bool rightLight)
{
    insert(Setting::Signal::RightLight::Start, Setting::Signal::RightLight::Length, rightLight);
}

void COMService::setWarningLightStatus(bool warningLight)
{
    insert(Setting::Signal::WarningLight::Start, Setting::Signal::WarningLight::Length, warningLight);
}