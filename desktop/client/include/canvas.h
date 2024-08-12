#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>

class Canvas : public QWidget
{

    int speedValue;
    int batteryValue;
    int tempValue;

public:
    explicit Canvas(QWidget *parent = nullptr);

    void setSpeedValue(int value)
    {
        speedValue = value;
        update();
    }
    void setBatteryValue(int value)
    {
        batteryValue = value;
        update();
    }
    void setTempValue(int value)
    {
        tempValue = value;
        update();
    }

protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // CANVAS_H
