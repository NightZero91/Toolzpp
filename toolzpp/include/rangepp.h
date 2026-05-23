#ifndef RANGEPP_H
#define RANGEPP_H
//--rangepp--toolzpp
//260505
#include <stdexcept>

namespace tlz
{
    namespace range
    {
        class Iter
        {
        public:
            int value;
            int step;
            int end;
            Iter(int _value, int _step, int _end) : value(_value), step(_step), end(_end) {};

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

        class Range
        {
        private:
            int m_begin, m_end, m_step;

        public:
            Range() = delete;
            // 构造（开始，结束，步长）
            Range(int e) : m_begin(0), m_end(e), m_step(1)
            {
                if (m_end < 0)
                    throw std::runtime_error("arg2 cannot < 0!");
            }
            Range(int b, int e) : m_begin(b), m_end(e), m_step(1)
            {
                if (m_end < m_begin)
                    throw std::runtime_error("arg2 cannot < arg1!");
            }
            Range(int b, int e, int s) : m_begin(b), m_end(e), m_step(s)
            {
                if (((m_end < m_begin)&&m_step > 0) ||((m_end > m_begin)&&m_step < 0) || m_step == 0)
                    throw std::runtime_error("arg2 cannot < arg1! or step cannot = 0!");
            }

            Range &operator=(const Range &) = delete;

            Range &operator=(Range &&) = delete;

            Range(Range &&) = delete;

            Iter begin() { return Iter(m_begin, m_step, m_end); }
            Iter end() { return Iter(m_end, m_step, m_end); }

            ~Range() = default;
        };
    }
}

#endif