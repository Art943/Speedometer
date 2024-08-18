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

    frame.MsgID = MSG_ID;           // The identifier of the receiver
    frame.FIR.B.RTR = CAN_no_RTR;   // Remote transmition set to 0, means this is a data frame
    frame.FIR.B.FF = CAN_frame_std; // Indicates standard ll bits long frame
    frame.FIR.B.DLC = BUFF_SIZE;    // Data Length Code, the length of the data

    int byte_count[frame.FIR.B.DLC]{0};
    while (Serial.available() > 0 && byte_count < frame.FIR.B.DLC)
    {
        frame.data.u8[byte_count] = Serial.read(); // Feed the can frame data from serial
    }

    CAN_write_frame(&frame);
}