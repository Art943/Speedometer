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

private:
    // Layout
    QGridLayout gridLayout;

    // Speed
    QLabel speedLabel;
    QSlider speedSlider;
    QLabel currentSpeedLabel;

    // Temperature
    QLabel temperatureLabel;
    QSlider temperatureSlider;
    QLabel currentTemperatureLabel;

    // Battery
    QLabel batteryLabel;
    QSlider batterySlider;
    QLabel currentBatteryLabel;

    // Checkbox
    QLabel lightSignalsLabel;
    QCheckBox leftCheckBox;
    QCheckBox rightCheckBox;
    QCheckBox warningCheckBox;
	QHBoxLayout checkboxLayout;
};

#endif
