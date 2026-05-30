#ifndef OUTPUTPP_H
#define OUTPUTPP_H
/**
 * @file outputpp.h
 * @date 2026-05-05
 * @author NightZero91
 * @brief 一个方便输入输出的文件
 * @note 欢迎使用者对该文件提出任何建议
 */
#include <iostream>
#include <string>
#include <vector>

namespace tlz
{
    /**
    *@brief 重载<<用于输出vector
    *@param o：输出对象
    *@param vec：要输出的vector
    */
    template <class Type>
    std::ostream& operator<<(std::ostream& o, const std::vector<Type>& vec)
    {
        o << "[";
        if (vec.empty())
        {
            o << "]";
            return o;
        }

        for (size_t i = 0; i < vec.size(); i++)
        {
            o << vec[i];
            if (i < vec.size() - 1) o << ",";
        }
        o << "]";

        return o;
    }

    /**
    *@brief 快速打印一行字符串（自动换行）
    *@param var：输出的字符串
    */
    namespace out 
    {
        inline void println(const std::string &var)
        {
            std::cout << var << "\n";
        }
    }

    namespace in
    {
        /**
        *@brief 快速输入一行字符
        *@return 输入的字符串
        */
        inline std::string input()
        {
            std::string s{};
            std::getline(std::cin, s);
            return s;
        }
    }
}


#endif