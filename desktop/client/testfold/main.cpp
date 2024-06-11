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
        // QFont sansFont("0xebdc", 12);
        QLabel *label = new QLabel(QChar(0xebdc)); // Specific icon character
        label->setFont(materialIconsFont);

        // Add the label to the layout
        layout->addWidget(label, 1, 1);
        layout->setAlignment(Qt::AlignCenter | Qt::AlignRight);

        QRectF rectangle(10.0, 20.0, 80.0, 60.0);
        int startAngle = 30 * 16;
        int spanAngle = 120 * 16;

        QPainter painter(this);
        painter.drawArc(rectangle, startAngle, spanAngle);
        layout->addWidget(painter.drawArc(rectangle, startAngle, spanAngle), Qt::AlignCenter);
    }
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Window gauge;
    gauge.show();

    return app.exec();
}
