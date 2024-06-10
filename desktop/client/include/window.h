#ifndef WINDOW_H
#define WINDOW_H

#include <QDialog>
#include <QGridLayout>

class Window : public QDialog
{

    QGridLayout layout;

public:
    Window()
    {
        setLayout(&layout);
        layout.setSizeConstraint(QGridLayout::SetFixedSize);
        setWindowTitle("Client");
    }
};

#endif