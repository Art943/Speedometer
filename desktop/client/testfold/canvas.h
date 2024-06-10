#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QFontDatabase>
#include <qpainter.h>

class Canvas : public QWidget
{
    void paintEvent(QPaintEvent *)
    {
        QPainter painter(this);
        QLineF line(10.0, 80.0, 90.0, 20.0);
        painter.drawLine(line);
        painter.background();
    }
    // RGB 64, 32, 60
};

#endif