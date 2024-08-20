#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QFont>
#include <QPainter>
#include <QMediaPlayer>
#include <QAudioOutput>

class Canvas : public QWidget
{
    int speedValue;
    int batteryValue;
    int tempValue;
    bool status;
    bool LeftLightstatus;
    bool RightLightstatus;
    int count = 0;
    QMediaPlayer turnSignalPlayer;
    QAudioOutput audioOutput;

public:
    Canvas();
    
    void setSpeedValue(int _speedValue);
    void setBatteryValue(int _batteryValue);
    void setTempValue(int _tempValue);
    void setConnection(bool _status);
    void setLeftLightStatus(bool _LeftLightstatus);
    void setRightLightStatus(bool _RightLightstatus);

protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // CANVAS_H
