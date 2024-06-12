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
        painter.drawRect(40, 15, 27, 70);
    }
};
// To set digitalspeed
class CustomSpeedLabel : public QLabel
{
public:
    explicit CustomSpeedLabel(const QString &text, QWidget *parent = nullptr)
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
        painter.drawRect(15, 75, 75, 30);

        int speeddigit = 240;
        // Draw the "km/h" text on top of the speed label
        painter.setPen(QPen(Qt::white));
        painter.setFont(QFont("Arial", 20));
        painter.drawText(rect(), Qt::AlignCenter | Qt::AlignBottom, QString::number(speeddigit) + " km/h");
    }
};

// Custom Widget class to draw the speed gauge
class SpeedGauge : public QWidget
{
public:
    explicit SpeedGauge(QWidget *parent = nullptr) : QWidget(parent)
    {
        setFixedSize(500, 500); // Set an appropriate size for the SpeedGauge widget
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
        painter.setPen(QPen(Qt::white, 7));

        // Define the rectangle and angles for the arc
        QRectF rect(5.0, 5.0, 485.0, 485.0);
        int startAngle = -30 * 16;
        int spanAngle = 240 * 16;
        // Draw the gauge arc
        painter.drawArc(rect, startAngle, spanAngle);
        // scales and speed
        painter.setPen(QPen(Qt::white, 6));
        for (int i = 0; i <= 12; ++i)
        {
            int angle = startAngle + (spanAngle / 12) * i;
            double radian = angle / 16.0 * M_PI / 180.0;
            int x1 = 250 + 220 * cos(radian);
            int y1 = 250 - 220 * sin(radian);
            int x2 = 250 + 240 * cos(radian);
            int y2 = 250 - 240 * sin(radian);
            painter.drawLine(x1, y1, x2, y2);

            // Draw scale numbers
            int speed = 240 - (i * 20);
            int xText = 250 + 180 * cos(radian);
            int yText = 250 - 180 * sin(radian);
            painter.drawText(xText - 15, yText + 5, QString::number(speed));
        }
        // Draw shorter scales between the main scales
        painter.setPen(QPen(Qt::white, 2));
        for (int i = 0; i < 60; ++i)
        {
            int angle = startAngle + (spanAngle / 60) * i;
            double radian = angle / 16.0 * M_PI / 180.0;
            int x1 = 250 + 230 * cos(radian);
            int y1 = 250 - 230 * sin(radian);
            int x2 = 250 + 240 * cos(radian); // Adjust this to touch the arc
            int y2 = 250 - 240 * sin(radian); // Adjust this to touch the arc
            painter.drawLine(x1, y1, x2, y2);
        }
        // Example: Draw the speed indicator (this would need to be dynamic in a real application)
        static const QPoint needle[3] = {
            QPoint(1, 10),
            QPoint(-1, 10),
            QPoint(0, -82)};

        int side = qMin(width(), height());

        painter.translate(width() / 2, height() / 2);
        painter.scale(side / 200.0, side / 200.0);

        const QColor needlecolor(Qt::red);
        painter.setBrush(needlecolor);
        painter.setPen(QPen(needlecolor, 3));
        int degrees = 50;
        painter.save();
        painter.rotate(1.0 * (degrees - 120));
        painter.drawConvexPolygon(needle, 3);
        painter.restore();
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
        materialIconsFont.setPointSize(80);

        QFont speedFont(materialIconsFontFamily);
        speedFont.setPointSize(80);

        QFont tempFont(materialIconsFontFamily);
        tempFont.setPointSize(40);

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

        int batteryValue = 0;

        QLabel *batteryPercentLabel = new QLabel(QString::number(batteryValue) + "%"); // Initial battery percentage
        batteryPercentLabel->setFont(QFont("Arial", 16));
        batteryPercentLabel->setStyleSheet("color: white;");

        QLabel *temp = new QLabel(QChar(0xe1ff)); // Another specific icon character
        temp->setFont(tempFont);
        temp->setStyleSheet("color: white; background-color: transparent;");

        int tempValue = 0;

        QLabel *tempLabel = new QLabel(QString::number(tempValue) + "°C"); // Initial temperature
        tempLabel->setFont(QFont("Arial", 16));
        tempLabel->setStyleSheet("color: white; background-color: transparent;");

        CustomSpeedLabel *speedwid = new CustomSpeedLabel(QChar(0xe9e4)); // Another specific icon character
        speedwid->setFont(speedFont);
        speedwid->setStyleSheet("color: white;");

        QLabel *Rturnsignal = new QLabel(QChar(0xe5c4)); // Another specific icon character
        Rturnsignal->setFont(materialIconsFont);

        QLabel *Lturnsignal = new QLabel(QChar(0xe5c8)); // Another specific icon character
        Lturnsignal->setFont(materialIconsFont);
        // Create a vertical layout for battery and temp
        QVBoxLayout *batteryTempLayout = new QVBoxLayout();
        batteryTempLayout->addWidget(temp, 0, Qt::AlignCenter);
        batteryTempLayout->addWidget(tempLabel, 0, Qt::AlignCenter); // Add temperature label
        batteryTempLayout->addWidget(battery, 0, Qt::AlignCenter);
        batteryTempLayout->addWidget(batteryPercentLabel, 0, Qt::AlignCenter);

        QLabel *nosignal = new QLabel(QChar(0xe628)); // Another specific icon character
        nosignal->setFont(speedFont);
        nosignal->setStyleSheet("color: red;");
        bool signal = true;
        bool Rightturnsignal = true;
        bool Leftturnsignal = true;
        if (Leftturnsignal)
        {
            Lturnsignal->setStyleSheet("color: green;");
        }
        else
        {
            Lturnsignal->setStyleSheet("color: rgb(64, 32, 60);");
        }
        if (Rightturnsignal)
        {
            Rturnsignal->setStyleSheet("color: green;");
        }
        else
        {
            Rturnsignal->setStyleSheet("color: rgb(64, 32, 60);");
        }

        QLabel *centralwidget;
        if (signal)
        {
            centralwidget = speedwid;
        }
        else
        {
            centralwidget = nosignal;
        }
        // Create and add the custom speed gauge widget
        SpeedGauge *speedGauge = new SpeedGauge();

        // Add the widgets to the grid layout with alignment
        layout->addWidget(Rturnsignal, 0, 0, Qt::AlignTop | Qt::AlignLeft);
        layout->addWidget(Lturnsignal, 0, 3, Qt::AlignTop | Qt::AlignRight);
        layout->addLayout(batteryTempLayout, 1, 3, Qt::AlignBottom | Qt::AlignRight);
        layout->addWidget(speedGauge, 0, 2, Qt::AlignCenter);
        layout->addWidget(centralwidget, 2, 2, Qt::AlignCenter | Qt::AlignBottom);
    }
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Window gauge;
    gauge.show();

    return app.exec();
}
