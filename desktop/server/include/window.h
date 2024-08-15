#ifndef WINDOW_H
#define WINDOW_H

#include <QDialog>
#include <QLabel>
#include <QSlider>
#include <QCheckBox>
#include <QGridLayout>
#include "setting.h"
#include "tcpservice.h"

class Window : public QDialog
{
    TCPService comservice;

public:
    Window();

private:
    void updateSpeedLabel(int value);
    void updateTemperatureLabel(int value);
    void updateBatteryLabel(int value);
    void onLeftLightToggled(bool checked);
    void onRightLightToggled(bool checked);
    void onWarningLightToggled(bool checked);

private:
    // Layout
    QGridLayout gridLayout;

    // Speed signal
    QLabel speedLabel;
    QSlider speedSlider;
    QLabel currentSpeedLabel;

    // Temperature signal
    QLabel temperatureLabel;
    QSlider temperatureSlider;
    QLabel currentTemperatureLabel;

    // Battery signal
    QLabel batteryLabel;
    QSlider batterySlider;
    QLabel currentBatteryLabel;

    // Light signal
    QLabel lightSignalsLabel;
    QCheckBox leftLight;
    QCheckBox rightLight;
    QCheckBox warningLight;
    QHBoxLayout checkboxLayout;
};

#endif
