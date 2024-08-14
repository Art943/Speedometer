#include <QApplication>
#include "window.h"
#include "tcpservice.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    TCPService service;

    Window gauge{service}; // Now it will use the default argument for the parent
    gauge.show();

    return app.exec();
}
