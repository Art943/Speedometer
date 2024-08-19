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
    Serial.println("Ready to send data...");

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

    if (pdTRUE == xQueueReceive(CAN_cfg.rx_queue, &frame, portMAX_DELAY))
    {
        if (frame.MsgID == MSG_ID)
        {
            Serial.write(frame.data.u8, frame.FIR.B.DLC);
        }
    }
    // Buffer to hold data
    // uint8_t buffer[3];

    // Send the data
    // Serial.write(buffer, sizeof(buffer));

    // Wait before sending the next set of data
    delay(20);
}