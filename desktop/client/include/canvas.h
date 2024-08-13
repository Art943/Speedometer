#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>

class Canvas : public QWidget
{

    int speedValue;
    int batteryValue;
    int tempValue;
    bool status;
    bool LeftLightstatus;
    bool RightLightstatus;
    bool WarningLightstatus;

public:
    explicit Canvas(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // CANVAS_H
