#include "window.h"

bool prevLeftLightStatus{false};
bool prevRightLightStatus{false};
bool warningLightStatus{false};

Window::Window(COMService &comservice_) : comservice(comservice_),
                                          gridLayout(this),
                                          speedLabel("Speed:", this),
                                          speedSlider(Qt::Horizontal, this),
                                          currentSpeedLabel(QString::number(Setting::Signal::Speed::Min) + QString(" Kph"), this),
                                          temperatureLabel("Temperature:", this),
                                          temperatureSlider(Qt::Horizontal, this),
                                          currentTemperatureLabel(QString::number(0) + QString(" °C")),
                                          batteryLabel("Battery Level:", this),
                                          batterySlider(Qt::Horizontal, this),
                                          currentBatteryLabel(QString::number(Setting::Signal::BatteryLevel::Min) + QString(" %"), this),
                                          lightSignalsLabel(Setting::Gui::Server::CheckBox::Label, this),
                                          leftLight(Setting::Gui::Server::CheckBox::ButtonLeft, this),
                                          rightLight(Setting::Gui::Server::CheckBox::ButtonRight, this),
                                          warningLight(Setting::Gui::Server::CheckBox::ButtonWarning, this)
{

    currentSpeedLabel.setFixedWidth(60); // Fixed width in order to avoid the resizing of the slider.

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

    // Battery Slider
    batterySlider.setMinimum(Setting::Signal::BatteryLevel::Min);
    batterySlider.setMaximum(Setting::Signal::BatteryLevel::Max);
    connect(&batterySlider, &QSlider::valueChanged, this, &Window::updateBatteryLabel);

    // Checkboxes
    connect(&leftLight, &QCheckBox::toggled, this, &Window::onLeftLightToggled);
    connect(&rightLight, &QCheckBox::toggled, this, &Window::onRightLightToggled);
    connect(&warningLight, &QCheckBox::toggled, this, &Window::onWarningLightToggled);

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
    checkboxLayout.addWidget(&leftLight);
    checkboxLayout.addWidget(&rightLight);
    checkboxLayout.addWidget(&warningLight);
    gridLayout.addLayout(&checkboxLayout, row, 1, 1, 2);

    // Set the layout
    setLayout(&gridLayout);
    gridLayout.setColumnStretch(1, 3); // Slider column Good chance that this is not needed
    gridLayout.setColumnStretch(2, 1); // Current value column Good chance that this is not needed
}

void Window::updateSpeedLabel(int value)
{
    comservice.setSpeed(value);
    currentSpeedLabel.setText(QString::number(value) + QString(" Kph"));
}

void Window::updateTemperatureLabel(int value)
{
    comservice.setTemperature(value);
    currentTemperatureLabel.setText(QString::number(value) + QString(" °C"));
}

void Window::updateBatteryLabel(int value)
{
    comservice.setBatteryLevel(value);
    currentBatteryLabel.setText(QString::number(value) + QString(" %"));
}

void Window::onLeftLightToggled(bool checked) // LEFT
{
    if (!warningLight.isChecked())
    {
        comservice.setLeftLightStatus(checked);
    }

    if (checked)
    {
        rightLight.setEnabled(false);
        rightLight.setStyleSheet(Setting::Gui::Server::CheckBox::ButtonDeactivated);
    }
    else
    {
        rightLight.setEnabled(true);
        rightLight.setStyleSheet(Setting::Gui::Server::CheckBox::ButtonReset);
    }
}

void Window::onRightLightToggled(bool checked) // RIGHT
{
    if (!warningLight.isChecked())
    {
        comservice.setRightLightStatus(checked);
    }

    if (checked)
    {
        leftLight.setEnabled(false);
        leftLight.setStyleSheet(Setting::Gui::Server::CheckBox::ButtonDeactivated);
    }
    else
    {
        leftLight.setEnabled(true);
        leftLight.setStyleSheet(Setting::Gui::Server::CheckBox::ButtonReset);
    }
}

void Window::onWarningLightToggled(bool checked)
{
    if (checked)
    {
        comservice.setLeftLightStatus(checked);
        comservice.setRightLightStatus(checked);
    }
    else
    {
        if (!leftLight.isEnabled())
        {
            comservice.setLeftLightStatus(false);
            comservice.setRightLightStatus(true);
        }
        else if (!rightLight.isEnabled())
        {
            comservice.setLeftLightStatus(true);
            comservice.setRightLightStatus(false);
        }
        else
        {
            comservice.setLeftLightStatus(false);
            comservice.setRightLightStatus(false);
        }
    }
}
