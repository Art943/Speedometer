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

        QString materialIconsFontFamily = "Material Icons";

        // Create a QFont object using the Material Icons font
        QFont materialIconsFont(materialIconsFontFamily);
        materialIconsFont.setPointSize(48);

        // Set a fixed size for the window
        const int fixedWidth = 600;
        const int fixedHeight = 400;
        setMinimumSize(fixedWidth, fixedHeight);
        setMaximumSize(fixedWidth, fixedHeight);

        // Set the background color
        setStyleSheet("background-color: rgb(64, 32, 60);");
        // QFont sansFont("0xebdc", 12);
        QLabel *label = new QLabel(QChar(0xe9e4)); // Specific icon character
        label->setFont(materialIconsFont);
        label->setAlignment(Qt::AlignCenter);

        // Add the label to the layout
        layout->addWidget(label, 0, 0);
    }
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Window gauge;
    gauge.show();

    return app.exec();
}
