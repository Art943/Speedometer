#ifndef WINDOW_H
#define WINDOW_H

#include <QDialog>
#include <QLabel>
#include <QSlider>
#include <QCheckBox>
#include <QGridLayout>
#include "setting.h"
#include "comservice.h"

class Window : public QDialog
{
    COMService &comservice;

public:
    Window(COMService &comservice_);

private:
    void updateSpeedLabel(int value);
    void updateTemperatureLabel(int value);
    void updateBatteryLabel(int value);
    void onLeftLightToggled(bool checked);
    void onRightLightToggled(bool checked);
    void onWarningLightToggled(bool checked);

private:
    // Settings
    // Setting::Signal &signal = Setting::Signal::getInstance();

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
