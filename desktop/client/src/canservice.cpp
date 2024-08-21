#include "canservice.h"

void CANService::run(void)
{
    QSerialPort serialPort;

    // Configure the serial port
    serialPort.setPortName(Setting::CAN::ClientPort);
    serialPort.setBaudRate(Setting::CAN::Baudrate);
    serialPort.setDataBits(QSerialPort::Data8);
    serialPort.setParity(QSerialPort::NoParity);
    serialPort.setStopBits(QSerialPort::OneStop);
    serialPort.setFlowControl(QSerialPort::NoFlowControl);

    // Open the serial port
    while (!serialPort.open(QIODevice::ReadOnly) && running)
    {
        QThread::sleep(1);
    }

    connectionStatus = true;

    while (running)
    {
        uint8_t temp_buffer[Setting::Signal::BUFFER_LENGTH];

        // Wait for data to be available for reading
        if (serialPort.waitForReadyRead(100))
        {
            // Read the data from the serial port
            QByteArray incomingData = serialPort.readAll();

            // Process the received data
            std::copy(incomingData.begin(), incomingData.end(), temp_buffer);

            mtx.lock();
            memcpy(buffer, temp_buffer, Setting::Signal::BUFFER_LENGTH);
            mtx.unlock();
        }

        // Allow other threads to run
        QThread::msleep(20);
    }

    // Close the serial port
    serialPort.close();
}