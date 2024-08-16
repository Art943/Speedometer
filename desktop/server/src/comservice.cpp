#include <climits>
#include "comservice.h"

void COMService::insert(int start, int length, uint32_t value)
{
    // Variable to start at the first relevant byte
    int bufferIndex{start / CHAR_BIT};

    // Variable to start at the first relevant bit
    int bitOffset{start % CHAR_BIT};

    // Variable to keep track of how many bits we've cleared/inserted
    int insertedBits{0};

    mtx.lock();

    // Insert the existing data from the buffer
    while (insertedBits < length)
    {
        // Target only the relevant bits in byte one
        uint8_t bitsLeftInByte = CHAR_BIT - bitOffset;

        // The amount of bits to clear; Either how many bits are left in the current byte, or the rest of the bits we want extracted, whichever is less.
        uint8_t bitsToInsert = (bitsLeftInByte < (length - insertedBits)) ? bitsLeftInByte : (length - insertedBits);

        // Make a mask covering the bits we want to clear from the current byte
        uint8_t mask = ((1 << bitsToInsert) - 1) << bitOffset;

        // Clear the relevant bits from the current byte in the buffer
        buffer[bufferIndex] &= ~mask;

        // Insert the new bits
        buffer[bufferIndex] |= ((value >> insertedBits) & ((1 << bitsToInsert) - 1)) << bitOffset;

        insertedBits += bitsToInsert;
        bitOffset = 0;
        bufferIndex++;
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