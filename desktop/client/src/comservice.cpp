#include "comservice.h"

void COMService::extract(int start, int length, uint32_t &value)
{
    uint32_t mask{0};

    for (size_t i = 0; i < start; i++)
    {
        mask << 1;
    }

    for (size_t i = 0; i < length; i++, mask << 1)
    {
        mask = mask | 1;
    }

    value = value & mask;
}

uint32_t COMService::extractSpeed()
{
    uint32_t speed{0};
    extract(Setting::Signal::Speed::Start, Setting::Signal::Speed::Length, speed);
    return speed;
}

uint32_t COMService::extractTemperature()
{
    uint32_t temperature{0};
    extract(Setting::Signal::Temperature::Start, Setting::Signal::Temperature::Length, temperature);
    return temperature;
}

uint32_t COMService::extractBatteryLevel()
{
    uint32_t batteryLevel{0};
    extract(Setting::Signal::BatteryLevel::Start, Setting::Signal::BatteryLevel::Length, batteryLevel);
    return batteryLevel;
}

bool COMService::leftLightStatus()
{
    uint32_t leftLight{0};
    extract(Setting::Signal::LeftLight::Start, Setting::Signal::LeftLight::Length, leftLight);
    return leftLight;
}

bool COMService::rightLightStatus()
{
    uint32_t rightLight{0};
    extract(Setting::Signal::RightLight::Start, Setting::Signal::RightLight::Length, rightLight);
    return rightLight;
}

bool COMService::warningLightStatus()
{
    uint32_t warningLight{0};
    extract(Setting::Signal::WarningLight::Start, Setting::Signal::WarningLight::Length, warningLight);
    return warningLight;
}

bool COMService::communicationStatus()
{
    bool comStatus{false};

    return comStatus;
}

uint8_t COMService::recieveBuffer()
{
}