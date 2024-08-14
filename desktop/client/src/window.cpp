#include "window.h"

Window::Window(COMService &com) : comservice(com)
{
    layout.addWidget(&canvas);
    this->setFixedSize(800, 560);
}

void Window::refreshCanvas()
{
    if (comservice.getStatus())
    {
        canvas.setSpeedValue(comservice.getSpeedValue);
        canvas.setBatteryValue(comservice.getBatteryValue);
        canvas.setTempValue(comservice.TempValue);
        canvas.setConnection(comservice.getConnection);
        canvas.setLeftLightStatus(comservice.getLeftLightStatus);
        canvas.setRightLightStatus(comservice.getLeftLightStatus);
        canvas.setWarningLightStatus(comservice.getLeftLightStatus);
    }
}
else
{
    canvas.setSpeedValue(0);     // Set the initial speed
    canvas.setBatteryValue(0);   // Set the initial battery percentage
    canvas.setTempValue(0);      // Set the initial temperature
    canvas.setConnection(false); // Set the initial Signals state
    canvas.setLeftLightStatus(false);
    canvas.setRightLightStatus(false);
    canvas.setWarningLightStatus(false);
}
canvas.update(); // Trigger repaint of the canvas
}
