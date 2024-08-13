#ifndef WINDOW_H
#define WINDOW_H

#include <QDialog>
#include <QTimer>
#include "canvas.h"
#include <QGridLayout>
#include "comservice.h"

class Window : public QDialog
{
    Canvas canvas;
    QTimer timer;
    QGridLayout layout;
    COMService &comservice;

public:
    explicit Window(COMService &com);

private:
    void refreshCanvas();
};

#endif // WINDOW_H
