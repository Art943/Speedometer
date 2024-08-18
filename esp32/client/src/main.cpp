#include <Arduino.h>
#include <CAN.h>
#include <CAN_config.h>

constexpr MSG_ID = 0x100;
constexpr BUFF_SIZE = 4;

CAN_device_t CAN_cfg;

void setup()
{
    Serial.begin(115200);

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
            for (int i = 0; i < frame.FIR.B.DLC; i++)
            {
                Serial.write(frame.data.u8[i]); // Feed to the data from CAN to the client via serial
            }
        }

        CAN_write_frame(&frame);
    }
}