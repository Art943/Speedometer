#include <QApplication>
#include "window.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Window gauge; // Now it will use the default argument for the parent
    gauge.show();

    return app.exec();
}
