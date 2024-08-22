#ifndef SETTING_H
#define SETTING_H

#include <map>
#include <string>

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
        constexpr signal_type(const char *str = "", signal_value _value = 0) : key{str}, value{_value} {}
    };

    template <std::size_t N>
    struct buffer
    {
        static constexpr std::size_t length(const signal_type *list)
        {
            return (list[N - 1].value.length + buffer<N - 1>::length(list));
        }

        static constexpr size_t size(const signal_type *list)
        {
            return (buffer<N>::length(list) / 8)
                       ? buffer<N>::length(list) / 8
                       : (buffer<N>::length(list) / 8 + 1);
        }
    };

    template <>
    struct buffer<1>
    {
        static constexpr std::size_t length(const signal_type *list)
        {
            return list[0].value.length;
        }
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

        std::map<std::string, signal_value> signal;

        Signal()
        {
            for (const auto &elem : list)
            {
                signal.emplace(elem.key, elem.value);
            }
        }

        Signal(Signal const &) = delete;
        void operator=(Signal const &) = delete;

    public:
        static constexpr std::size_t BUFFER_LENGTH{((buffer<sizeof(list) / sizeof(list[0])>::size(list)))};

        static Signal &getInstance()
        {
            static Signal instance;
            return instance;
        }

        signal_value operator[](const std::string &key) const
        {
            return signal.at(key);
        }
    };

    namespace Client
    {
        constexpr int WindowHeight{560};
        constexpr int WindowWidth{800};
    }

    namespace Server
    {
        constexpr int WindowHeight{125};
        constexpr int WindowWidth{800};
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

    int constexpr INTERVAL{40};
}

#endif