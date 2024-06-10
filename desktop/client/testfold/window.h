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
        int fontId = QFontDatabase::addApplicationFont(":/res/font.ttf");
        if (fontId == -1)
        {
            qWarning() << "Failed to load the font file!";
        }
        else
        {
            QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);
            if (!fontFamilies.isEmpty())
            {
                QString fontFamily = fontFamilies.at(0); // Use the first family

                // Create a label and set the custom font
                QLabel *label = new QLabel("This text uses the custom font.");
                QFont customFont(fontFamily);
                label->setFont(customFont);

                // Add the label to the layout
                layout->addWidget(label, 0, 0);
            }
        }

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
