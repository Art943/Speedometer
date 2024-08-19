#include <Arduino.h>

void setup()
{
    Serial.begin(115200, SERIAL_8N1);

    while (!Serial)
    {
        delay(10);
    }

    Serial.println("Ready to send data...");
}

void loop()
{
    // Buffer to hold data
    uint8_t buffer[3];

    // !!! Test code to be removed and replaced with proper data handling !!!
    for (size_t i = 0; i < sizeof(buffer); i++)
    {
        buffer[i] = random(0, 256);
    }
    // !!! End of test code !!!

    // Send the data
    Serial.write(buffer, sizeof(buffer));

    // Wait before sending the next set of data
    delay(20);
}