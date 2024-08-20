#include <CAN.h>
#include <Arduino.h>
#include <CAN_config.h>
#include "setting.h"

constexpr int MSG_ID = 0x100;

CAN_device_t CAN_cfg;

void setup()
{
<<<<<<< HEAD
    delay(2000);
    Serial.begin(SETTING::CAN::Baudrate);
    // Serial.begin(115200);
=======
    Serial.begin(115200);
    // Serial.begin(SETTING::CAN::Baudrate);
>>>>>>> e3d840102eced838f4e792fc78e9de3007e9787b

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