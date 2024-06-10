#include <QApplication>
#include <QDialog>
#include <QGridLayout>
#include <QFont>
#include <QLabel>
#include <QDebug>

class Window : public QDialog
{
public:
    Window(QDialog *parent = nullptr) : QDialog(parent)
    {
        // Create a grid layout
        QGridLayout *layout = new QGridLayout(this);

        // Set a fixed size for the window
        const int fixedWidth = 600;
        const int fixedHeight = 400;
        setMinimumSize(fixedWidth, fixedHeight);
        setMaximumSize(fixedWidth, fixedHeight);

        // Set the background color
        setStyleSheet("background-color: rgb(64, 32, 60);");
    }
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Window gauge;
    gauge.show();

    return app.exec();
}
