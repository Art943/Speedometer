#include "window.h"

Window::Window(COMService &com) : comservice(com)
{
    layout.addWidget(&canvas, 0, 0);
    this->setLayout(&layout);
    this->setFixedSize(Setting::Gui::Client::Width, Setting::Gui::Client::Height);
    layout.setContentsMargins(0, 0, 0, 0);

    // Connect the timer's timeout signal to the refreshCanvas slot
    connect(&timer, &QTimer::timeout, this, &Window::refreshCanvas);

    // Start the timer
    timer.start(Setting::Gui::Client::Interval);
}

void Window::refreshCanvas()
{
    if (comservice.connected())
    {
        canvas.setSpeedValue(comservice.getSpeed());
        canvas.setBatteryValue(comservice.getBatteryLevel());
        canvas.setTempValue(comservice.getTemperature());
        canvas.setConnection(comservice.connected());
        canvas.setLeftLightStatus(comservice.getLeftLightStatus());
        canvas.setRightLightStatus(comservice.getRightLightStatus());
    }
    else
    {
        canvas.setSpeedValue(0);
        canvas.setBatteryValue(0);
        canvas.setTempValue(0);
        canvas.setConnection(false);
        canvas.setLeftLightStatus(false);
        canvas.setRightLightStatus(false);
    }

    canvas.update();
}
