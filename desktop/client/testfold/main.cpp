#include <QApplication>
#include <QDialog>
#include <QGridLayout>
#include <QFont>
#include <QLabel>
class Window : public QDialog
{
public:
    Window(QDialog *parent = nullptr) : QDialog(parent)
    {
        // Create a grid layout
        QGridLayout *layout = new QGridLayout(this);
        Qlabel label;

        // Load the font

        // Set a fixed size for the window
        const int fixedWidth = 600;
        const int fixedHeight = 400;
        setMinimumSize(fixedWidth, fixedHeight);
        setMaximumSize(fixedWidth, fixedHeight);

        // Set the background color
        setStyleSheet("background-color: rgb(64, 32, 60);");
        QFont sansFont("0xebdc", 12);
        label->sansFont("0xebdc", 12);
        layout->addWidget(label, 0, 1);
    }
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Window gauge;
    gauge.show();

    return app.exec();
}
