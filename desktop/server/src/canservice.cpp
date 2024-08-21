#include "canservice.h"

void CANService::run(void)
{
    QSerialPort serialPort;

    // Configure the serial port
    serialPort.setPortName(Setting::CAN::ServerPort);
    serialPort.setBaudRate(Setting::CAN::Baudrate);
    serialPort.setDataBits(QSerialPort::Data8);
    serialPort.setParity(QSerialPort::NoParity);
    serialPort.setStopBits(QSerialPort::OneStop);
    serialPort.setFlowControl(QSerialPort::NoFlowControl);

    // Open the serial port
    while (!serialPort.open(QIODevice::WriteOnly))
    {
        std::cout << "Trying to open Serial Port..." << std::endl;
        QThread::sleep(1);
    }

    while (running)
    {
        uint8_t temp_buffer[Setting::Signal::BUFFER_LENGTH];

        mtx.lock();
        memcpy(temp_buffer, buffer, Setting::Signal::BUFFER_LENGTH);
        mtx.unlock();

        QByteArray outgoingData(reinterpret_cast<const char *>(temp_buffer), Setting::Signal::BUFFER_LENGTH);

        // Example: Sending data to the microcontroller
        serialPort.write(outgoingData);

        // Ensure all data is sent
        serialPort.waitForBytesWritten(100);

        // Allow other threads to run and give some time between iterations
        QThread::msleep(20);
    }

    // Close the serial port
    serialPort.close();
}