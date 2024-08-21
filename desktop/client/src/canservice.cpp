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
    while (running)
    {
        if (!connectionStatus)
        {
            // Open the serial port
            while (!serialPort.open(QIODevice::ReadOnly) && running)
            {
                std::cout << "Attempting to connect..." << std::endl;
                QThread::sleep(1);
            }
            connectionStatus = true;
        }

        uint8_t tempBuffer[Setting::Signal::BUFFER_LENGTH];
        int bytesRead;

        // Wait for data to be available for reading
        if (serialPort.waitForReadyRead(100))
        {
            // Read the data from the serial port
            bytesRead = serialPort.read(reinterpret_cast<char *>(tempBuffer), Setting::Signal::BUFFER_LENGTH);

            if (bytesRead == Setting::Signal::BUFFER_LENGTH)
            {
                mtx.lock();
                memcpy(buffer, tempBuffer, Setting::Signal::BUFFER_LENGTH);
                mtx.unlock();
            }
        }
        else
        {
            // Close the serial port and mark the connection as lost
            serialPort.close();
            connectionStatus = false;
        }

        // Allow other threads to run
        QThread::msleep(20);
    }

    // Close the serial port
    if (serialPort.isOpen())
    {
        serialPort.close();
    }
}