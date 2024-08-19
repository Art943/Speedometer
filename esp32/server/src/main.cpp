#include <Arduino.h>

void setup()
{
    Serial.begin(115200, SERIAL_8N1);

    while (!Serial)
    {
        delay(10);
    }

    Serial.println("Ready to recieve data...");
}

void loop()
{
    static uint8_t buffer[3];
    static size_t bytesReceived = 0;

    while (Serial.available() > 0)
    {
        buffer[bytesReceived] = Serial.read(); // Read a byte
        bytesReceived++;

        if (bytesReceived == sizeof(buffer))
        {
            // Once the buffer is full, process the data

            // !!! Placeholder used for testing, replace with proper handling of data !!!
            Serial.print("Received data: ");
            for (size_t i = 0; i < sizeof(buffer); i++)
            {
                Serial.print(buffer[i], HEX);
                Serial.print(" ");
            }
            Serial.println();
            // !!! End of placeholder !!!

            // Reset the counter for the next set of data
            bytesReceived = 0;
        }
    }
}