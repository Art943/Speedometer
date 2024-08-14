#ifndef SETTING_H
#define SETTING_H

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
            constexpr int InitValue{0};
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

        namespace WarningLight
        {
            constexpr int Min{0};
            constexpr int Max{1};
            constexpr int Start{24};
            constexpr int Length{1};
        }

        constexpr int BUFFER_LENGTH{4};
    }

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

            namespace Signal
            {
                namespace Speed
                {
                    const char *const Unit{" Kph"};
                    const char *const Label{"Speed:"};
                    constexpr int LabelFixWidth{50};
                }

                namespace Temperature
                {
                    const char *const Unit{" °C"};
                    const char *const Label{"Temperature:"};
                }

                namespace Battery
                {
                    const char *const Unit{" %"};
                    const char *const Label{"Battery Level:"};
                }

                namespace CheckBox
                {
                    const char *const Label{"Ligth Signals:"};
                    const char *const ButtonLeft{"Left"};
                    const char *const ButtonRight{"Right"};
                    const char *const ButtonWarning{"Warning"};
                    const char *const ButtonDeactivated{"color: gray;"};
                    const char *const ButtonReset{""};
                }
            }
        }
    }
}

#endif