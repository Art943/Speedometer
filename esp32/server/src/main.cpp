#include <CAN.h>
#include <Arduino.h>
#include <CAN_config.h>
#include "setting.h"

constexpr int MSG_ID = 0x100;

CAN_device_t CAN_cfg;

void setup()
{
    Serial.begin(SETTING::CAN::Baudrate);

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

    if (BUFF_SIZE == Serial.readBytes(frame.data.u8, SETTING::Signal::BUFFER_LENGTH))
    {
        CAN_write_frame(&frame);
    }
}