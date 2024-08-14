#ifndef WINDOW_H
#define WINDOW_H

#include <QDialog>
#include <QLabel>
#include <QSlider>
#include <QCheckBox>
#include <QGridLayout>
#include <setting.h>

class Window : public QDialog
{
public:
    Window();

private:
    void updateSpeedLabel(int value);
    void updateTemperatureLabel(int value);
    void updateBatteryLabel(int value);
    void onLeftCheckBoxToggled(bool checked);
    void onRightCheckBoxToggled(bool checked);
    void onWarningCheckBoxToggled(bool checked);

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
    QCheckBox leftCheckBox;
    QCheckBox rightCheckBox;
    QCheckBox warningCheckBox;
    QHBoxLayout checkboxLayout;
};

#endif
