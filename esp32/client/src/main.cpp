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

    // Send the data
    Serial.write(buffer, sizeof(buffer));

    // Wait before sending the next set of data
    delay(20);
}
