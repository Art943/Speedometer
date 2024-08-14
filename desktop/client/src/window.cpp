#include "window.h"

Window::Window(COMService &com) : comservice(com)
{
    layout.addWidget(&canvas, 0, 0);
    this->setFixedSize(800, 560);
    timer.setInterval(40);
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
