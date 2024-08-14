#include <QApplication>
#include "window.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    
    Window server;
    server.show();

    return app.exec();
}
