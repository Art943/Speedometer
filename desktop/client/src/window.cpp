#include "window.h"

Window::Window(COMService &com) : comservice(com)
{
    layout.addWidget(&canvas, 0, 0);
    this->setLayout(&layout);
    this->setFixedSize(800, 560);
    layout.setContentsMargins(0, 0, 0, 0);

    // Connect the timer's timeout signal to the refreshCanvas slot
    connect(&timer, &QTimer::timeout, this, &Window::refreshCanvas);

    // Start the timer
    timer.start(40);
}

void Window::refreshCanvas()
{
    if (comservice.connectionStatus())
    {
        canvas.setSpeedValue(comservice.getSpeed());
        canvas.setBatteryValue(comservice.getBatteryLevel());
        canvas.setTempValue(comservice.getTemperature());
        canvas.setConnection(comservice.connectionStatus());
        canvas.setLeftLightStatus(comservice.getLeftLightStatus());
        canvas.setRightLightStatus(comservice.getRightLightStatus());
    }
    else
    {
        canvas.setSpeedValue(0);
        canvas.setBatteryValue(0);
        canvas.setTempValue(0);
        canvas.setConnection(false);
        canvas.setLeftLightStatus(true);
        canvas.setRightLightStatus(true);
    }

    canvas.update();
}
