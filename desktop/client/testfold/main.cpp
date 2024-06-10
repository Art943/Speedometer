#include <QApplication>
#include <QDialog>
#include <QGridLayout>
#include <QFontDatabase>
#include <QLabel>
#include <QDebug>
class Window : public QDialog
{
public:
    Window(QDialog *parent = nullptr) : QDialog(parent)
    {
        // Create a grid layout
        QGridLayout *layout = new QGridLayout(this);

        // Load the font

        // Set a fixed size for the window
        const int fixedWidth = 600;
        const int fixedHeight = 400;
        setMinimumSize(fixedWidth, fixedHeight);
        setMaximumSize(fixedWidth, fixedHeight);

        // Set the background color
        setStyleSheet("background-color: rgb(64, 32, 60);");
        int fontId = QFontDatabase::addApplicationFont(":/res/font.ttf");

        QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);
        QString materialIconsFontFamily = fontFamilies.at(0);
        QWidget window;
        // Create a label and set the icon
        QLabel *iconLabel = new QLabel(&window);
        QFont iconFont(materialIconsFontFamily);
        iconFont.setPointSize(48); // Set the desired font size
        iconLabel->setFont(iconFont);
        iconLabel->setText(QChar(0xebdc)); // Unicode for the desired icon
        layout->addWidget(iconLabel);
    }
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Window gauge;
    gauge.show();

    return app.exec();
}
