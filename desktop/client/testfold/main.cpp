#include <QApplication>
#include <QDialog>
#include <QGridLayout>
#include <QFont>
#include <QLabel>
#include <QPainter>

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
        materialIconsFont.setPointSize(110);

        // Set a fixed size for the window
        const int fixedWidth = 800;
        const int fixedHeight = 560;
        setMinimumSize(fixedWidth, fixedHeight);
        setMaximumSize(fixedWidth, fixedHeight);

        // Set the background color
        setStyleSheet("background-color: rgb(64, 32, 60);");

        QLabel *battery = new QLabel(QChar(0xebdc)); // Specific icon character
        battery->setFont(materialIconsFont);
        battery->setStyleSheet("color: white;");

        QLabel *speed = new QLabel(QChar(0xe9e4)); // Another specific icon character
        speed->setFont(materialIconsFont);
        speed->setStyleSheet("color: white;");

        QLabel *temp = new QLabel(QChar(0xe1ff)); // Another specific icon character
        temp->setFont(materialIconsFont);
        temp->setStyleSheet("color: white;");

        QLabel *Rturnsignal = new QLabel(QChar(0xe5c4)); // Another specific icon character
        Rturnsignal->setFont(materialIconsFont);
        Rturnsignal->setStyleSheet("color: green;");

        QLabel *Lturnsignal = new QLabel(QChar(0xe5c8)); // Another specific icon character
        Lturnsignal->setFont(materialIconsFont);
        Lturnsignal->setStyleSheet("color: green;");

        // Add the batterys to the layout with alignment
        layout->addWidget(battery, 2, 3, Qt::AlignRight);
        layout->addWidget(speed, 2, 2, Qt::AlignCenter | Qt::AlignBottom);
        layout->addWidget(temp, 1, 3, Qt::AlignRight);
        layout->addWidget(Rturnsignal, 0, 0, Qt::AlignTop | Qt::AlignLeft);
        layout->addWidget(Lturnsignal, 0, 3, Qt::AlignTop | Qt::AlignRight);
    }
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Window gauge;
    gauge.show();

    return app.exec();
}
