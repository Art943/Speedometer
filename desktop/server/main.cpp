#include <QApplication>
#include "window.h"
#include "tcpservice.h"

int main(int argc, char **argv)
{
    TCPService tcpService;
    QApplication app(argc, argv);

    Window server{tcpService};
    server.show();

    return app.exec();
}
