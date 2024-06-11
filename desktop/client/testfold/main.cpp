#include <QApplication>
#include <QDialog>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QFont>
#include <QLabel>
#include <QPainter>
#include <QWidget>

// Custom QLabel class to allow painting over the battery
class CustomLabel : public QLabel
{
public:
    explicit CustomLabel(const QString &text, QWidget *parent = nullptr)
        : QLabel(text, parent)
    {
    }

protected:
    void paintEvent(QPaintEvent *event) override
    {
        QLabel::paintEvent(event);

        QPainter painter(this);

        painter.setRenderHint(QPainter::Antialiasing);
        QPalette pal = this->palette();
        QColor bgColor = pal.color(backgroundRole());
        painter.setBrush(bgColor);
        painter.setPen(bgColor);
        painter.drawRect(49, 23, 50, 100);
    }
};

// Custom Widget class to draw the speed gauge
class SpeedGauge : public QWidget
{
public:
    explicit SpeedGauge(QWidget *parent = nullptr) : QWidget(parent)
    {
        setFixedSize(510, 510); // Set an appropriate size for the SpeedGauge widget
    }

protected:
    void paintEvent(QPaintEvent *event) override
    {
        QWidget::paintEvent(event);

        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        // Set the brush color to transparent for the gauge background
        painter.setBrush(Qt::transparent);

        // Set pen for the gauge
        painter.setPen(QPen(Qt::white, 10));

        // Define the rectangle and angles for the arc
        QRectF rect(50.0, 50.0, 450.0, 450.0);
        int startAngle = -30 * 16;
        int spanAngle = 240 * 16;

        // Draw the gauge arc
        painter.drawArc(rect, startAngle, spanAngle);

        // Example: Draw the speed indicator (this would need to be dynamic in a real application)
        painter.setPen(QPen(Qt::red, 5));
        painter.drawLine(rect.center(), rect.center() + QPointF(180 * cos(M_PI / 6), 180 * sin(M_PI / 6)));
    }
};

class Window : public QDialog
{
public:
    Window(QDialog *parent = nullptr) : QDialog(parent)
    {
        // Create a grid layout
        QGridLayout *layout = new QGridLayout(this);

        QString materialIconsFontFamily = "Material Icons";

        // Create QFont objects using the Material Icons font with different sizes
        QFont materialIconsFont(materialIconsFontFamily);
        materialIconsFont.setPointSize(110);

        QFont speedFont(materialIconsFontFamily);
        speedFont.setPointSize(80);

        QFont tempFont(materialIconsFontFamily);
        tempFont.setPointSize(50);

        // Set a fixed size for the window
        const int fixedWidth = 800;
        const int fixedHeight = 560;
        setMinimumSize(fixedWidth, fixedHeight);
        setMaximumSize(fixedWidth, fixedHeight);

        // Set the background color
        setStyleSheet("background-color: rgb(64, 32, 60);");

        CustomLabel *battery = new CustomLabel(QChar(0xebdc)); // Specific icon character
        battery->setFont(materialIconsFont);
        battery->setStyleSheet("color: white;");

        QLabel *speed = new QLabel(QChar(0xe9e4)); // Another specific icon character
        speed->setFont(speedFont);
        speed->setStyleSheet("color: white;");

        QLabel *temp = new QLabel(QChar(0xe1ff)); // Another specific icon character
        temp->setFont(tempFont);
        temp->setStyleSheet("color: white;");

        QLabel *Rturnsignal = new QLabel(QChar(0xe5c4)); // Another specific icon character
        Rturnsignal->setFont(materialIconsFont);
        Rturnsignal->setStyleSheet("color: green;");

        QLabel *Lturnsignal = new QLabel(QChar(0xe5c8)); // Another specific icon character
        Lturnsignal->setFont(materialIconsFont);
        Lturnsignal->setStyleSheet("color: green;");

        // Create a vertical layout for battery and temp
        QVBoxLayout *batteryTempLayout = new QVBoxLayout();
        batteryTempLayout->addWidget(temp, 0, Qt::AlignCenter);
        batteryTempLayout->addWidget(battery, 0, Qt::AlignRight);

        // Create and add the custom speed gauge widget
        SpeedGauge *speedGauge = new SpeedGauge();

        // Add the widgets to the grid layout with alignment
        layout->addWidget(Rturnsignal, 0, 0, Qt::AlignTop | Qt::AlignLeft);
        layout->addWidget(Lturnsignal, 0, 3, Qt::AlignTop | Qt::AlignRight);
        layout->addLayout(batteryTempLayout, 1, 3, Qt::AlignBottom | Qt::AlignRight);
        layout->addWidget(speedGauge, 0, 2);
        layout->addWidget(speed, 2, 2, Qt::AlignCenter | Qt::AlignBottom);
    }
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Window gauge;
    gauge.show();

    return app.exec();
}
