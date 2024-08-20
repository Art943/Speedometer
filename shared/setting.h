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
}

#endif