#ifndef SETTING_H
#define SETTING_H

#include <string>
#include <map>
#include <memory>
#include <stdexcept>

namespace Setting
{
    namespace Signal
    {
        namespace Speed
        {
            constexpr int Min{0};
            constexpr int Max{240};
            constexpr int Start{0};
            constexpr int Length{8};
        }

        namespace Temperature
        {
            constexpr int Min{-60};
            constexpr int Max{60};
            constexpr int Start{8};
            constexpr int Length{7};
        }

        namespace BatteryLevel
        {
            constexpr int Min{0};
            constexpr int Max{100};
            constexpr int Start{15};
            constexpr int Length{7};
        }

        namespace LeftLight
        {
            constexpr int Min{0};
            constexpr int Max{1};
            constexpr int Start{22};
            constexpr int Length{1};
        }

        namespace RightLight
        {
            constexpr int Min{0};
            constexpr int Max{1};
            constexpr int Start{23};
            constexpr int Length{1};
        }

        constexpr int BUFFER_LENGTH{3};
    }

    // Struct to hold signal properties
    struct SignalProperties
    {
        int Min;
        int Max;
        int Start;
        int Length;
    };

    namespace Gui
    {
        namespace Server
        {
            namespace MainWindow
            {
                const char *const Title{"Server"};
                constexpr int FixWidth{600};
                constexpr int FixHeight{125};
            }

            namespace CheckBox
            {
                const char *const Label{"Light Signals:"};
                const char *const ButtonLeft{"Left"};
                const char *const ButtonRight{"Right"};
                const char *const ButtonWarning{"Warning"};
                const char *const ButtonDeactivated{"color: gray;"};
                const char *const ButtonReset{""};
            }
        }
    }

    namespace CAN
    {
        constexpr int Baudrate{115200};
        const char *const ClientPort{"/dev/ttyUSB0"};
        const char *const ServerPort{"/dev/ttyUSB1"};
    }

    namespace TCP
    {
        constexpr int PORT{12345};
        const char *const IP{"127.0.0.1"};
    }

    namespace Windowfixed
    {
        constexpr int INTERVAL{40};
        constexpr int HEIGHT{560};
        constexpr int WIDTH{800};
    }
    class SignalManager
    {
    public:
        // Singleton access method
        static SignalManager& getInstance()
        {
            static SignalManager instance;
            return instance;
        }

        // Add signal to the map
        void addSignal(const std::string& name, const SignalProperties& properties)
        {
            signalMap[name] = properties;
        }

        // Get signal properties by name
        SignalProperties getSignal(const std::string& name) const
        {
            auto it = signalMap.find(name);
            if (it != signalMap.end())
            {
                return it->second;
            }
            else
            {
                throw std::runtime_error("Signal not found");
            }
        }

    private:
        // Private constructor for singleton
        SignalManager()
        {
            // Preload signals into the map during initialization
            addSignal("Speed", { Signal::Speed::Min, Signal::Speed::Max, Signal::Speed::Start, Signal::Speed::Length });
            addSignal("Temperature", { Signal::Temperature::Min, Signal::Temperature::Max, Signal::Temperature::Start, Signal::Temperature::Length });
            addSignal("BatteryLevel", { Signal::BatteryLevel::Min, Signal::BatteryLevel::Max, Signal::BatteryLevel::Start, Signal::BatteryLevel::Length });
            addSignal("LeftLight", { Signal::LeftLight::Min, Signal::LeftLight::Max, Signal::LeftLight::Start, Signal::LeftLight::Length });
            addSignal("RightLight", { Signal::RightLight::Min, Signal::RightLight::Max, Signal::RightLight::Start, Signal::RightLight::Length });
        }

        // Disallow copying
        SignalManager(const SignalManager&) = delete;
        SignalManager& operator=(const SignalManager&) = delete;

        // Map to store signal properties
        std::map<std::string, SignalProperties> signalMap;
    };
}

#endif
