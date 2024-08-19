#include "window.h"
#include <QApplication>

#ifdef COMM_CAN
#include "canservice.h"
#else
#include "tcpservice.h"
#endif

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

#ifdef COMM_CAN
    CANService comservice;
#else
    TCPService comservice;
#endif

    Window window(comservice);
    window.show();

    return app.exec();
}
