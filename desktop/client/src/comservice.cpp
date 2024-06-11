#include "comservice.h"

void COMService::extract(int start, int length, uint32_t &value)
{
    uint32_t mask{0};

    value = 0;

    for (size_t i = 0; i < length; i++)
    {
        mask |= (1 << i);
    }

    mask <<= start;

    // Mask Complete!
}

uint32_t COMService::getSpeed()
{
    uint32_t speed{0};

    mtx.lock();
    extract(Setting::Signal::Speed::Start, Setting::Signal::Speed::Length, speed);
    mtx.unlock();

    return speed;
}

int32_t COMService::getTemperature()
{
    uint32_t temperature{0};

    mtx.lock();
    extract(Setting::Signal::Temperature::Start, Setting::Signal::Temperature::Length, temperature);
    mtx.unlock();

    if (is_negative(temperature, Setting::Signal::Temperature::Length))
    {
        return convert_to_negative(temperature, Setting::Signal::Temperature::Length);
    }

    return temperature;
}

uint32_t COMService::getBatteryLevel()
{
    uint32_t batteryLevel{0};

    mtx.lock();
    extract(Setting::Signal::BatteryLevel::Start, Setting::Signal::BatteryLevel::Length, batteryLevel);
    mtx.unlock();

    return batteryLevel;
}

bool COMService::leftLightStatus()
{
    uint32_t leftLight{0};

    mtx.lock();
    extract(Setting::Signal::LeftLight::Start, Setting::Signal::LeftLight::Length, leftLight);
    mtx.unlock();

    return leftLight;
}

bool COMService::rightLightStatus()
{
    uint32_t rightLight{0};

    mtx.lock();
    extract(Setting::Signal::RightLight::Start, Setting::Signal::RightLight::Length, rightLight);
    mtx.unlock();

    return rightLight;
}

bool COMService::warningLightStatus()
{
    uint32_t warningLight{0};

    mtx.lock();
    extract(Setting::Signal::WarningLight::Start, Setting::Signal::WarningLight::Length, warningLight);
    mtx.unlock();

    return warningLight;
}

/* Helper Functions */

bool is_negative(uint32_t num, size_t len)
{
    return (num & (1 << (len - 1))) != 0;
}

int32_t convert_to_negative(uint32_t num, size_t len)
{
    uint32_t mask = 0;

    for (size_t i = 0; i < len; i++)
    {
        mask |= (1 << i);
    }

    return -(((~num) + 1) & mask);
}