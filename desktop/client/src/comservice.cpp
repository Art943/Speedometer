#include <climits>
#include "comservice.h"

void COMService::extract(int start, int length, uint32_t &value)
{
    uint32_t value{0};

    uint8_t byteIndex{start / CHAR_BIT};
    uint8_t bitOffset{start % CHAR_BIT};

    uint8_t extractedBits{0};

    mtx.lock();
    while (extractedBits < length)
    {
        uint8_t bitsLeftInByte = CHAR_BIT - bitOffset;
        uint8_t bitsToExtract = (bitsLeftInByte < (length - extractedBits)) ? bitsLeftInByte : (length - extractedBits);

        uint8_t mask = ((1 << bitsToExtract) - 1) << bitOffset;
        uint8_t extractedBits = (buffer[byteIndex] & mask) >> bitOffset;

        value |= static_cast<uint32_t>(extractedBits) << extractedBits;

        extractedBits += bitsToExtract;
        bitOffset = 0;
        byteIndex++;
    }
    mtx.unlock();
}

uint32_t COMService::getSpeed()
{
    uint32_t speed{0};

    extract(Setting::Signal::Speed::Start, Setting::Signal::Speed::Length, speed);

    return speed;
}

int32_t COMService::getTemperature()
{
    uint32_t value{0};
    int32_t temperature{0};

    extract(Setting::Signal::Temperature::Start, Setting::Signal::Temperature::Length, value);

    if ((value & (1 << (Setting::Signal::Temperature::Length - 1))) != 0)
    {
        uint32_t mask = 0;

        for (size_t i = 0; i < Setting::Signal::Temperature::Length; i++)
        {
            mask |= (1 << i);
        }

        temperature = -(((~value) + 1) & mask);
    }
    else
    {
        temperature = value;
    }

    return temperature;
}

uint32_t COMService::getBatteryLevel()
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