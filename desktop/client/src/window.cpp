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

    // Initialize and start the timer
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Window::refreshCanvas);
    timer->start(40); // 40 ms interval
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

void Window::refreshCanvas()
{
    canvas->update(); // Trigger repaint of the canvas
}
