#include <QApplication>
#include "window.h"
#include "tcpservice.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    TCPservice service;

    Window gauge; // Now it will use the default argument for the parent
    gauge.show(service);

    return app.exec();
}
