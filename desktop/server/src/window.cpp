#include "window.h"

Window::Window() : gridLayout(this),
                   speedLabel(Setting::Gui::Server::Signal::Speed::Label, this),
                   speedSlider(Qt::Horizontal, this),
                   currentSpeedLabel(QString::number(Setting::Signal::Speed::Min), this),
                   temperatureLabel(Setting::Gui::Server::Signal::Temperature::Label, this),
                   temperatureSlider(Qt::Horizontal, this),
                   batteryLabel(Setting::Gui::Server::Signal::Battery::Label, this),
                   batterySlider(Qt::Horizontal, this),
                   currentBatteryLabel(QString::number(Setting::Signal::BatteryLevel::Min), this),
                   lightSignalsLabel(Setting::Gui::Server::Signal::CheckBox::Label, this),
                   leftCheckBox(Setting::Gui::Server::Signal::CheckBox::ButtonLeft, this),
                   rightCheckBox(Setting::Gui::Server::Signal::CheckBox::ButtonRight, this),
                   warningCheckBox(Setting::Gui::Server::Signal::CheckBox::ButtonWarning, this)
{

    currentSpeedLabel.setFixedWidth(Setting::Gui::Server::Signal::Speed::LabelFixWidth); // Fixed width in order to avoid the resizing of the slider.

    // Main window title and fixed Width-Height
    setWindowTitle(Setting::Gui::Server::MainWindow::Title);
    setFixedWidth(Setting::Gui::Server::MainWindow::FixWidth);
    setFixedHeight(Setting::Gui::Server::MainWindow::FixHeight);

    // Speed Slider
    speedSlider.setMinimum(Setting::Signal::Speed::Min);
    speedSlider.setMaximum(Setting::Signal::Speed::Max);
    connect(&speedSlider, &QSlider::valueChanged, this, &Window::updateSpeedLabel);

    // Temperature Slider
    temperatureSlider.setMinimum(Setting::Signal::Temperature::Min);
    temperatureSlider.setMaximum(Setting::Signal::Temperature::Max);
    connect(&temperatureSlider, &QSlider::valueChanged, this, &Window::updateTemperatureLabel);

    // Initial temperature when gui starts
    updateTemperatureLabel(Setting::Signal::Temperature::InitValue);

    // Battery Slider
    batterySlider.setMinimum(Setting::Signal::BatteryLevel::Min);
    batterySlider.setMaximum(Setting::Signal::BatteryLevel::Max);
    connect(&batterySlider, &QSlider::valueChanged, this, &Window::updateBatteryLabel);

    // Checkboxes
    connect(&leftCheckBox, &QCheckBox::toggled, this, &Window::onLeftCheckBoxToggled);
    connect(&rightCheckBox, &QCheckBox::toggled, this, &Window::onRightCheckBoxToggled);

    int row = 0; // The row index improves the readability of the code

    // Add Speed Slider to the grid layout
    gridLayout.addWidget(&speedLabel, row, 0, 1, 1, Qt::AlignRight);
    gridLayout.addWidget(&speedSlider, row, 1, 1, 3); // Span 3 columns
    gridLayout.addWidget(&currentSpeedLabel, row, 4);
    row++;

    // Add Temperature Slider to the grid layout
    gridLayout.addWidget(&temperatureLabel, row, 0, 1, 1, Qt::AlignRight);
    gridLayout.addWidget(&temperatureSlider, row, 1, 1, 3); // Span 3 columns
    gridLayout.addWidget(&currentTemperatureLabel, row, 4);
    row++;

    // Add Battery Slider to the grid layout
    gridLayout.addWidget(&batteryLabel, row, 0, 1, 1, Qt::AlignRight);
    gridLayout.addWidget(&batterySlider, row, 1, 1, 3); // Span 3 columns
    gridLayout.addWidget(&currentBatteryLabel, row, 4);
    row++;

    // Add Checkboxes to the grid layout
    gridLayout.addWidget(&lightSignalsLabel, row, 0, 1, 1, Qt::AlignRight);
    checkboxLayout.addWidget(&leftCheckBox);
    checkboxLayout.addWidget(&rightCheckBox);
    checkboxLayout.addWidget(&warningCheckBox);
    gridLayout.addLayout(&checkboxLayout, row, 1, 1, 2);

    // Set the layout
    setLayout(&gridLayout);
    gridLayout.setColumnStretch(1, 3); // Slider column Good chance that this is not needed
    gridLayout.setColumnStretch(2, 1); // Current value column Good chance that this is not needed
}

void Window::updateSpeedLabel(int value)
{
    currentSpeedLabel.setText(QString::number(value) + Setting::Gui::Server::Signal::Speed::Unit);
}

void Window::updateTemperatureLabel(int value)
{
    currentTemperatureLabel.setText(QString::number(value) + Setting::Gui::Server::Signal::Temperature::Unit);
}

void Window::updateBatteryLabel(int value)
{
    currentBatteryLabel.setText(QString::number(value) + Setting::Gui::Server::Signal::Battery::Unit);
}

void Window::onLeftCheckBoxToggled(bool checked)
{
    if (checked)
    {
        rightCheckBox.setEnabled(false);                                                        // Disable Right checkbox
        rightCheckBox.setStyleSheet(Setting::Gui::Server::Signal::CheckBox::ButtonDeactivated); // Gray out Right checkbox
    }
    else
    {
        rightCheckBox.setEnabled(true);                                                   // Enable Right checkbox
        rightCheckBox.setStyleSheet(Setting::Gui::Server::Signal::CheckBox::ButtonReset); // Remove gray out effect
    }
}

void Window::onRightCheckBoxToggled(bool checked)
{
    if (checked)
    {
        leftCheckBox.setEnabled(false);                                                        // Disable Left checkbox
        leftCheckBox.setStyleSheet(Setting::Gui::Server::Signal::CheckBox::ButtonDeactivated); // Gray out Left checkbox
    }
    else
    {
        leftCheckBox.setEnabled(true);                                                   // Enable Left checkbox
        leftCheckBox.setStyleSheet(Setting::Gui::Server::Signal::CheckBox::ButtonReset); // Remove gray out effect
    }
}
