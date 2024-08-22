#ifndef SETTING_H
#define SETTING_H

#include <map>
#include <string>
#include <stddef.h>

namespace Setting
{
    struct signal_value
    {
        int min, max, start, length;
        constexpr signal_value(int _min = 0, int _max = 0, int _start = 0, int _length = 0) : min{_min}, max{_max}, start{_start}, length{_length} {}
    };

    struct signal_type
    {
        const char *key;
        signal_value value;
        constexpr signal_type(const char *str = "", signal_value _value = {}) : key{str}, value{_value} {}
    };

    class Signal
    {
    private:
        static constexpr signal_type list[]{
            {"Speed", {0, 240, 0, 8}},
            {"Temperature", {-60, 60, 8, 7}},
            {"BatteryLevel", {0, 100, 15, 7}},
            {"LeftLight", {0, 1, 22, 1}},
            {"RightLight", {0, 1, 23, 1}}};

        std::map<std::string, signal_type> signal;

        Signal()
        {
            for (const auto &elem : list)
            {
                signal.emplace(elem.key, elem.value);
            }
        }

        Signal(Signal const &) = delete;
        void operator=(Signal const &) = delete;

        /*template <std::size_t N>
        static constexpr std::size_t calculateLength()
        {
            return N != 0 ? list[N].value.length + calculateLength<N - 1>() : list[0].value.length;
        }*/

    public:
        static constexpr std::size_t BUFFER_LENGTH = 3; // (calculateLength<(sizeof(list) / sizeof(list[0]) - 1)>() + 7) / 8;

        static Signal &getInstance()
        {
            static Signal instance;
            return instance;
        }

        signal_type operator[](const std::string &key) const
        {
            return signal.at(key);
        }
    };

    namespace Client
    {
        constexpr int WindowHeight{640};
        constexpr int WindowWidth{800};
    }

    namespace Server
    {
        constexpr int WindowHeight{150};
        constexpr int WindowWidth{800};
    }

    int constexpr INTERVAL{40};

#ifdef COMM_CAN
    namespace CAN
    {
        constexpr int Baudrate{115200};
        const char *const ClientPort{"/dev/ttyUSB0"};
        const char *const ServerPort{"/dev/ttyUSB1"};
    }
#else
    namespace TCP
    {
        constexpr int PORT{12345};
        const char *const IP{"127.0.0.1"};
    }
#endif

}

#endif