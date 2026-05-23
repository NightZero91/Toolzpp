#ifndef PROGRESSBARPP_H
#define PROGRESSBARPP_H
//@--progressbarpp--toolzpp
//260515
#include <stdexcept>
#include <ostream>
#include <string>
#include <iostream>
namespace tlz
{
    namespace cmdui 
    {
        class ProgressBar
        {
        private:
            char fill_char;
            double value;
            double min;
            double max;
            unsigned int width;
            std::string name;
        public:
            ProgressBar() = delete;
            ProgressBar(double _value, unsigned int _width, double _min, double _max, char _fill_char = '#', const std::string& _name = "Bar") : 
            value(_value), width(_width), fill_char(_fill_char), name(_name), min(_min), max(_max) 
            {                
                if (min > max) throw std::invalid_argument("Bar min_value cannot > max_value.");
                if (min == max) throw std::invalid_argument("Bar min,max cannot same.");
                if (value > max) throw std::invalid_argument("Bar value cannot > max.");
                if (value < min) throw std::invalid_argument("Bar value cannot < min.");
            }
            ~ProgressBar() {}

            friend std::ostream& operator<<(std::ostream& o, const ProgressBar &other)
            {
                double percent = (other.value - other.min) / (other.max - other.min);
                int filled = static_cast<int>(percent * other.width + 0.5);
                o << other.name << ":[";
                for (int i = 0; i < filled; ++i)
                {
                    o << other.fill_char;
                }
                for (int i = 0; i < (other.width - filled); ++i)
                {
                    o << ' ';
                }
                int tmp = percent * 100;
                o << "]" << tmp << "%";
                return o;
            }

            void set_value(double _value)
            {
                if (_value > max) throw std::invalid_argument("Bar value cannot > max.");
                if (_value < min) throw std::invalid_argument("Bar value cannot < min.");
                value = _value;
            }

            double get_value() const noexcept
            {
                return value;
            }

            void print(std::ostream& o = std::cout) const 
            {
                o << '\r' << *this << std::flush;
            }
        };
    }
}


#endif