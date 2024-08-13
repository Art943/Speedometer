#include "window.h"
#include <QGridLayout>

Window::Window(QDialog *parent) : QDialog(parent)
{
    QGridLayout *layout = new QGridLayout(this);

    canvas = new Canvas();
    layout->addWidget(canvas, 0, 0);

    canvas->setSpeedValue(0);   // Set the initial speed
    canvas->setBatteryValue(0); // Set the initial battery percentage
    canvas->setTempValue(0);    // Set the initial temperature
    canvas->setSignalsValue(0); // Set the initial Signals state
}

void Window::updateSpeed(int speed)
{
    canvas->setSpeedValue(speed);
}

void Window::updateBattery(int battery)
{
    canvas->setBatteryValue(battery);
}
void Window::updateTemperature(int temperature)
{
    canvas->setTempValue(temperature);
}

void Window::updateSignals(int turnsignals)
{
    canvas->setSignalsValue(turnsignals);
}
void Window::refreshCanvas()
{
    canvas->update(); // Trigger repaint of the canvas
}
