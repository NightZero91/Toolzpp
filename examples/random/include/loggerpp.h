#ifndef LOGGERPP_H
#define LOGGERPP_H
/**
 * @file loggerpp.h
 * @date 2026-05-29
 * @author NightZero91
 * @brief 一个日志类，用于输出日志
 * @note 欢迎使用者对该文件提出任何建议
 * @warning 多线程请确保加锁
*/

#include <iostream>
#include <ostream>
#include <string>
#include <stdexcept>

namespace tlz
{
    /**
    *@brief 枚举日志类型
    */
    enum class LogType
    {
        INFO,
        WARN,
        ERROR,
        DEBUG,
        FATAL
    };
    namespace logger 
    {
        class Logger
        {
        public:
            /**
            *@brief 写日志
            *@param os：输出流对象
            *@param msg：输出信息
            *@param type：日志的类型
            *@note msg类型为const char*
            */
            static void write_log(std::ostream& os, const char* msg, LogType type)
            {
                switch (type) 
                {
                case LogType::INFO:
                    os << "[INFO]:" << msg << "\n";
                    break;
                case LogType::WARN:
                    os << "[WARN]:" << msg << "\n";
                    break;
                case LogType::DEBUG:
                    os << "[DEBUG]:" << msg << "\n";
                    break;
                case LogType::ERROR:
                    os << "[ERROR]:" << msg << "\n";
                    break;
                case LogType::FATAL:
                    os << "[FATAL]:" << msg << "\n";
                    break;
                default:
                    throw std::runtime_error("Unknown log type.");
                    break;
                }
            }
            /**
            *@brief 写日志
            *@param os：输出流对象
            *@param msg：输出信息
            *@param type：日志的类型
            *@note msg类型为std::string
            */
            static void write_log(std::ostream& os, const std::string &msg, LogType type)
            {
                switch (type) 
                {
                case LogType::INFO:
                    os << "[INFO]:" << msg << "\n";
                    break;
                case LogType::WARN:
                    os << "[WARN]:" << msg << "\n";
                    break;
                case LogType::DEBUG:
                    os << "[DEBUG]:" << msg << "\n";
                    break;
                case LogType::ERROR:
                    os << "[ERROR]:" << msg << "\n";
                    break;
                case LogType::FATAL:
                    os << "[FATAL]:" << msg << "\n";
                    break;
                default:
                    throw std::runtime_error("Unknown log type.");
                    break;
                }
            }

            /**
            *@brief 在控制台打印日志
            *@param msg：输出信息
            *@param type：日志的类型
            *@note msg类型为const char*
            */
            static void console_log(LogType type, const std::string &msg)
            {
                write_log(std::cout, msg, type);
            }
            /**
            *@brief 在控制台打印日志
            *@param msg：输出信息
            *@param type：日志的类型
            *@note msg类型为std::string
            */
            static void console_log(LogType type, const char *msg)
            {
                write_log(std::cout, msg, type);
            }
        };
    }
    using log = tlz::logger::Logger;
}

#endif