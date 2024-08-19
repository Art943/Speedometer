#include <CAN.h>
#include <Arduino.h>
#include <CAN_config.h>
#include "setting.h"

constexpr int MSG_ID = 0x100;

CAN_device_t CAN_cfg;

void setup()
{
    Serial.begin(SETTING::CAN::Baudrate);
    // Serial.begin(SETTING::CAN::Baudrate, SERIAL_8N1);
    while (!Serial)
    {
        delay(10);
    }
    Serial.println("Ready to recieve data...");

    // Config the communication
    CAN_cfg.tx_pin_id = GPIO_NUM_5;
    CAN_cfg.rx_pin_id = GPIO_NUM_35;
    CAN_cfg.speed = CAN_SPEED_500KBPS;
    CAN_cfg.rx_queue = xQueueCreate(1, sizeof(CAN_frame_t));

    (void)CAN_init(); // initialize CAN Module
}

void loop()
{
    CAN_frame_t frame{0};

    frame.MsgID = MSG_ID;                             // The identifier of the receiver
    frame.FIR.B.RTR = CAN_no_RTR;                     // Remote transmition set to 0, means this is a data frame
    frame.FIR.B.FF = CAN_frame_std;                   // Indicates standard ll bits long frame
    frame.FIR.B.DLC = SETTING::Signal::BUFFER_LENGTH; // Data Length Code, the length of the data

    if (SETTING::Signal::BUFFER_LENGTH == Serial.readBytes(frame.data.u8, SETTING::Signal::BUFFER_LENGTH))
    {
        CAN_write_frame(&frame);
        // static uint8_t buffer[3];
        // static size_t bytesReceived = 0;

        // while (Serial.available() > 0)
        // {
        //     buffer[bytesReceived] = Serial.read(); // Read a byte
        //     bytesReceived++;

        //     if (bytesReceived == sizeof(buffer))
        //     {
        // Once the buffer is full, process the data

        // // !!! Placeholder used for testing, replace with proper handling of data !!!
        // Serial.print("Received data: ");
        // for (size_t i = 0; i < sizeof(buffer); i++)
        // {
        //     Serial.print(buffer[i], HEX);
        //     Serial.print(" ");
        // }
        // Serial.println();
        // // !!! End of placeholder !!!

        // Reset the counter for the next set of data
        // bytesReceived = 0;
        // }
    }
}