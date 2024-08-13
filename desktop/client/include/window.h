#ifndef WINDOW_H
#define WINDOW_H

#include <QDialog>
#include <QTimer>
#include "canvas.h"

class Window : public QDialog
{
    Canvas *canvas;
    QTimer *timer;

public:
    explicit Window(QDialog *parent = nullptr);
    ~Window() {}

    void updateSpeed(int speed);
    void updateBattery(int battery);
    void updateTemperature(int temperature);
    void updateSignals(int turnsignals);

private:
    void refreshCanvas();
};

#endif // WINDOW_H
