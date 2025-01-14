#include <CAN.h>
#include <Arduino.h>
#include <CAN_config.h>
#include "setting.h"

CAN_device_t CAN_cfg;

void setup()
{
    Serial.begin(Setting::CAN::Baudrate);

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
        Serial.write(frame.data.u8, frame.FIR.B.DLC);
    }
}
