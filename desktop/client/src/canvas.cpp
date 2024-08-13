#include "canvas.h"
#include <QPainter>
#include <QFont>

Canvas::Canvas(QWidget *parent)
    : QWidget(parent), speedValue(0), batteryValue(0), tempValue(0), signalsValue(0)
{
    setFixedSize(800, 560);
}

void Canvas::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Background color
    painter.fillRect(rect(), QColor(64, 32, 60));

    // Speed gauge arc
    QRectF rect(155.0, 35.0, 490.0, 490.0);
    int startAngle = -30 * 16;
    int spanAngle = 240 * 16;
    painter.setPen(QPen(Qt::white, 7));
    painter.drawArc(rect, startAngle, spanAngle);

    // Scales and speed numbers
    painter.setPen(QPen(Qt::white, 6));
    for (int i = 0; i <= 12; ++i)
    {
        int angle = startAngle + (spanAngle / 12) * i;
        double radian = angle / 16.0 * M_PI / 180.0;
        int x1 = 400 + 220 * cos(radian);
        int y1 = 280 - 220 * sin(radian);
        int x2 = 400 + 240 * cos(radian);
        int y2 = 280 - 240 * sin(radian);
        painter.drawLine(x1, y1, x2, y2);

        // Draw scale numbers
        int speed = 240 - (i * 20);
        int xText = 400 + 180 * cos(radian);
        int yText = 280 - 180 * sin(radian);
        painter.setFont(QFont("Arial", 16));
        painter.drawText(xText - 15, yText + 5, QString::number(speed));
    }

    // Draw shorter scales between the main scales
    painter.setPen(QPen(Qt::white, 2));
    for (int i = 0; i < 60; ++i)
    {
        int angle = startAngle + (spanAngle / 60) * i;
        double radian = angle / 16.0 * M_PI / 180.0;
        int x1 = 400 + 230 * cos(radian);
        int y1 = 280 - 230 * sin(radian);
        int x2 = 400 + 240 * cos(radian);
        int y2 = 280 - 240 * sin(radian);
        painter.drawLine(x1, y1, x2, y2);
    }

    // Speed indicator (needle)
    static const QPoint needle[3] = {
        QPoint(1, 10),
        QPoint(-1, 10),
        QPoint(0, -82)};

    int side = qMin(width(), height());

    painter.translate(width() / 2, height() / 2);
    painter.scale(side / 200.0, side / 200.0);

    const QColor needlecolor(Qt::red);
    painter.setBrush(needlecolor);
    painter.setPen(QPen(needlecolor, 3));
    painter.save();
    painter.rotate(1.0 * (speedValue - 120));
    painter.drawConvexPolygon(needle, 3);
    painter.restore();

    // Battery icon
    painter.resetTransform();
    painter.setFont(QFont("Material Icons", 110));
    painter.drawText(650, 420, QChar(0xebdc));
    QColor batteryColor = Qt::green;
    if (batteryValue < 25)
    {
        batteryColor = Qt::red;
    }
    else if (batteryValue >= 25 && batteryValue < 50)
    {
        batteryColor = Qt::yellow;
    }
    else if (batteryValue >= 50)
    {
        batteryColor = Qt::green;
    }
    painter.setPen(batteryColor);
    // Battery percentage
    painter.setFont(QFont("Arial", 16));
    painter.setPen(Qt::white);
    painter.drawText(700, 440, QString::number(batteryValue) + "%");

    QColor tempColor = Qt::white;
    // Temperature icon

    if (tempValue >= 5 && tempValue <= 39)
    {
        tempColor = Qt::blue;
    }
    else if (tempValue > 39)
    {
        tempColor = Qt::red;
    }
    painter.setPen(tempColor);
    painter.setFont(QFont("Material Icons", 50));
    painter.drawText(690, 250, QChar(0xe1ff));
    painter.setFont(QFont("Arial", 16));

    painter.setPen(Qt::white);
    painter.drawText(700, 270, QString::number(tempValue) + "°C");
    // Speed icon
    painter.setFont(QFont("Material Icons", 80));
    painter.drawText(350, 500, QChar(0xe9e4));

    // Speed value
    painter.setFont(QFont("Arial", 16));
    painter.drawText(370, 520, QString::number(speedValue) + " km/h");

    // Turn signals
    painter.setFont(QFont("Material Icons", 80));
    QString backgroundColor = "rgb(64, 32, 60)"; // Your background color

    if (signalsValue)
    {
        ;
    }
    painter.drawText(650, 100, QChar(0xe5c8)); // Left turn signal
    painter.drawText(50, 100, QChar(0xe5c4));  // Right turn signal
}
