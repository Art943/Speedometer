#include "window.h"

Window::Window() : gridLayout(this),
                   speedLabel("Speed:", this),
                   speedSlider(Qt::Horizontal, this),
                   currentSpeedLabel(QString::number(Setting::Signal::Speed::Min), this),
                   temperatureLabel("Temperature:", this),
                   temperatureSlider(Qt::Horizontal, this),
                   batteryLabel("Battery Level:", this),
                   batterySlider(Qt::Horizontal, this),
                   currentBatteryLabel(QString::number(Setting::Signal::BatteryLevel::Min), this),
                   lightSignalsLabel("Light Signals:", this),
                   leftCheckBox("Left", this),
                   rightCheckBox("Right", this),
                   warningCheckBox("Warning", this)
{

    currentSpeedLabel.setFixedWidth(50); // Fixed width in order to avoid the resizing of the slider.

    setWindowTitle("Server"); // Title for the main window
    setFixedWidth(600);       // Fixed width for the main window
    setFixedHeight(125);

    // Speed Slider
    speedSlider.setMinimum(Setting::Signal::Speed::Min);
    speedSlider.setMaximum(Setting::Signal::Speed::Max);
    connect(&speedSlider, &QSlider::valueChanged, this, &Window::updateSpeedLabel);

    // Temperature Slider
    temperatureSlider.setMinimum(Setting::Signal::Temperature::Min);
    temperatureSlider.setMaximum(Setting::Signal::Temperature::Max);
    connect(&temperatureSlider, &QSlider::valueChanged, this, &Window::updateTemperatureLabel);

    // Initial temperature set to 0 instead of -60
    updateTemperatureLabel(0);

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
    currentSpeedLabel.setText(QString::number(value) + " Kph");
}

void Window::updateTemperatureLabel(int value)
{
    currentTemperatureLabel.setText(QString::number(value) + " °C");
}

void Window::updateBatteryLabel(int value)
{
    currentBatteryLabel.setText(QString::number(value) + " %");
}

void Window::onLeftCheckBoxToggled(bool checked)
{
    if (checked)
    {
        rightCheckBox.setEnabled(false);             // Disable Right checkbox
        rightCheckBox.setStyleSheet("color: gray;"); // Gray out Right checkbox
    }
    else
    {
        rightCheckBox.setEnabled(true);  // Enable Right checkbox
        rightCheckBox.setStyleSheet(""); // Remove gray out effect
    }
}

void Window::onRightCheckBoxToggled(bool checked)
{
    if (checked)
    {
        leftCheckBox.setEnabled(false);             // Disable Left checkbox
        leftCheckBox.setStyleSheet("color: gray;"); // Gray out Left checkbox
    }
    else
    {
        leftCheckBox.setEnabled(true);  // Enable Left checkbox
        leftCheckBox.setStyleSheet(""); // Remove gray out effect
    }
}
