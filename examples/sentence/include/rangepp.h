#ifndef RANGEPP_H
#define RANGEPP_H
/**
* @file rangepp.h
* @date 2026-05-05
* @author NightZero91
* @brief 简单的range类
* @note 仅提供了基础功能，推荐用于范围for遍历
*/
#include <stdexcept>

namespace tlz
{
    namespace range
    {
        /**
        *@brief range迭代器
        *@param value：值
        *@param step：步长
        *@param end：停止
        */
        class Iter
        {
        public:
            int value;
            int step;
            int end;
            Iter(int _value, int _step, int _end) : value(_value), step(_step), end(_end) {};
            //自增，解引用，不等号等重载
            Iter &operator++()
            {
                value += step;
                return *this;
            }

            int operator*() const { return value; }

            bool operator!=(const Iter &) const {
                if (step > 0) return value < end;
                else return value > end;
            }          

            ~Iter() = default;
        };
        /**
        *@brief range类
        *@param m_begin：起始
        *@param m_end：结束
        *@param m_step：步长
        */
        class Range
        {
        private:
            int m_begin, m_end, m_step;
        public:
            Range() = delete;
            /**
            *@brief 构造range对象
            *@param e：结束
            */
            Range(int e) : m_begin(0), m_end(e), m_step(1)
            {
                if (m_end < 0)
                    throw std::runtime_error("arg2 cannot < 0!");
            }
            /**
            *@brief 构造range对象
            *@param b：起始
            *@param e：结束
            */
            Range(int b, int e) : m_begin(b), m_end(e), m_step(1)
            {
                if (m_end < m_begin)
                    throw std::runtime_error("arg2 cannot < arg1!");
            }
            /**
            *@brief 构造range对象
            *@param b：起始
            *@param e：结束
            *@param s：步长
            */
            Range(int b, int e, int s) : m_begin(b), m_end(e), m_step(s)
            {
                if (((m_end < m_begin)&&m_step > 0) ||((m_end > m_begin)&&m_step < 0) || m_step == 0)
                    throw std::runtime_error("arg2 cannot < arg1! or step cannot = 0!");
            }

            Range &operator=(const Range &) = delete;

            Range &operator=(Range &&) = delete;

            Range(Range &&) = delete;
            /**
            *@brief 获取起始迭代器
            *@return 起始迭代器类
            */
            Iter begin() { return Iter(m_begin, m_step, m_end); }
            /**
            *@brief 获取结束迭代器
            *@return 结束迭代器类
            */
            Iter end() { return Iter(m_end, m_step, m_end); }

            ~Range() = default;
        };
    }
}

#endif