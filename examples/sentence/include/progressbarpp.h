#ifndef PROGRESSBARPP_H
#define PROGRESSBARPP_H
/**
 * @file progressbarpp.h
 * @date 2026-05-15
 * @author NightZero91
 * @brief 一个实用的进度条，对cmd小工具十分合适
 * @note 欢迎使用者对该文件提出任何建议
 * @warning 多线程记得加锁哦~
 */
#include <stdexcept>
#include <ostream>
#include <string>
#include <iostream>
namespace tlz
{
    namespace cmdui 
    {
        /**
        *@brief 一个控制台进度条类
        */
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
            /**
            *@brief 构造一个进度条
            *@param _value：进度条的值
            *@param _width：进度条宽度
            *@param _min：进度条所表现的最小值
            *@param _max：进度条所表现的最大值
            *@param _fill_char：填充进度条的字符
            *@param _name：进度条名字
            */
            ProgressBar(double _value, unsigned int _width, double _min, double _max, char _fill_char = '#', const std::string& _name = "Bar") : 
            value(_value), width(_width),  min(_min), max(_max) ,fill_char(_fill_char), name(_name)
            {                
                if (min > max) throw std::invalid_argument("Bar min_value cannot > max_value.");
                if (min == max) throw std::invalid_argument("Bar min,max cannot same.");
                if (value > max) throw std::invalid_argument("Bar value cannot > max.");
                if (value < min) throw std::invalid_argument("Bar value cannot < min.");
            }
            ~ProgressBar() {}
            /**
            *@brief ostream输出重载函数
            */
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
            /**
            *@brief 设置进度条的值
            *@param _value：进度条值
            */
            void set_value(double _value)
            {
                if (_value > max) throw std::invalid_argument("Bar value cannot > max.");
                if (_value < min) throw std::invalid_argument("Bar value cannot < min.");
                value = _value;
            }
            /**
            *@brief 获取进度条的值
            *@return 进度条的值
            */
            double get_value() const noexcept
            {
                return value;
            }
            /**
            *@brief 用ostream在控制台上输出进度条(覆盖)
            */
            void print(std::ostream& o = std::cout) const 
            {
                o << '\r' << *this << std::flush;
            }
        };
    }
}


#endif