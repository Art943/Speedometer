#include <climits>
#include "comservice.h"

void COMService::extract(int start, int length, uint32_t &value)
{
    // Variable to start at the first relevant byte
    int bufferIndex{start / CHAR_BIT};

    // Variable to start at the first relevant bit
    int bitOffset{start % CHAR_BIT};

    // Variable to keep track of how many bits we've extracted
    int extractedBits{0};

    mtx.lock();
    while (extractedBits < length)
    {
        // Target only the relevant bits in byte one
        uint8_t bitsLeftInByte = CHAR_BIT - bitOffset;

        // The amount of bits to extract; Either how many bits are left in the current byte, or the rest of the bits we want extracted, whichever is less.
        uint8_t bitsToExtract = (bitsLeftInByte < (length - extractedBits)) ? bitsLeftInByte : (length - extractedBits);

        // Make a mask covering the bits we want to extract from the current byte
        uint8_t mask = ((1 << bitsToExtract) - 1) << bitOffset;

        // Extract the bits we want from the current byte in the buffer
        uint8_t extractedData = (buffer[bufferIndex] & mask) >> bitOffset;

        // Store extracted bits in it's proper place in "value"
        value |= static_cast<uint32_t>(extractedData) << extractedBits;

        extractedBits += bitsToExtract;
        bitOffset = 0;
        bufferIndex++;
    }
    mtx.unlock();
}

void COMService::extract(int start, int length, int32_t &value)
{
    extract(start, length, reinterpret_cast<uint32_t &>(value));

    if ((value & (1 << (length - 1))) != 0)
    {
        value |= (~0U << length);
    }
}

uint32_t COMService::getSpeed()
{
    uint32_t speed{0};

    extract(Setting::Signal::Speed::Start, Setting::Signal::Speed::Length, speed);

    return speed;
}

int32_t COMService::getTemperature()
{
    int32_t temperature{0};

    extract(Setting::Signal::Temperature::Start, Setting::Signal::Temperature::Length, temperature);

    return temperature;
}

uint32_t COMService::getBatteryLevel()
{
    uint32_t batteryLevel{0};

    extract(Setting::Signal::BatteryLevel::Start, Setting::Signal::BatteryLevel::Length, batteryLevel);

    return batteryLevel;
}

bool COMService::getLeftLightStatus()
{
    uint32_t leftLight{0};

    extract(Setting::Signal::LeftLight::Start, Setting::Signal::LeftLight::Length, leftLight);

    return leftLight;
}

bool COMService::getRightLightStatus()
{
    uint32_t rightLight{0};

    extract(Setting::Signal::RightLight::Start, Setting::Signal::RightLight::Length, rightLight);

    return rightLight;
}