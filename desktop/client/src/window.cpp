#include "window.h"

Window::Window(COMService &com) : comservice(com)
{
    layout.addWidget(&canvas, 0, 0);
    this->setLayout(&layout);
    this->setFixedSize(800, 560);
    // Set up the timer with an interval of 40 ms
    timer.setInterval(40);

    // Connect the timer's timeout signal to the refreshCanvas slot
    connect(&timer, &QTimer::timeout, this, &Window::refreshCanvas);

    // Start the timer
    timer.start();
}

void Window::refreshCanvas()
{
    canvas.setSpeedValue(comservice.getSpeed());
    canvas.setBatteryValue(comservice.getBatteryLevel());
    canvas.setTempValue(comservice.getTemperature());
    canvas.setConnection(comservice.connected());
    canvas.setLeftLightStatus(comservice.getLeftLightStatus());
    canvas.setRightLightStatus(comservice.getRightLightStatus());
}
