#ifndef COUNTERPP_H
#define COUNTERPP_H
/**
 * @file counterpp.h
 * @date 2026-05-15
 * @author NightZero91
 * @brief 一个简单的计数器类，代临时/长期的计数变量，提高代码可读性
 * @note 欢迎使用者对该文件提出任何建议
 * @note 计数器可以重设，人生不能重来.
 * @warning 多线程请确保加锁
 */
#include <type_traits>
namespace tlz
{
    namespace counter
    {
        class Counter
        {
        private:
            //计数器的计数值
            long long count;
            //调用reset函数时的默认恢复值
            long long start_count;
        public:
            /**
            *@brief 无参构造，将默认恢复值和计数器数值设为0
            */
                Counter() : count(0), start_count(0) {};
            /**
            *@brief 自定义构造计数器
            *@param _count：起始数值
            *@param _start_count：默认恢复值
            */
            Counter(long long _count, long long _start_count) : count(_count), start_count(_start_count) {};
            ~Counter() = default;

            /**
            *@brief 重设计数值为指定值
            *@param _count：指定值
            */
            void reset(long long _count) noexcept
            {
                count = _count;
            }

            /**
            *@brief 重设计数值为默认恢复值
            */
            void reset() noexcept
            {
                count = start_count;
            }

            /**
            *@brief 重设默认恢复值
            *@param _start_count：默认恢复值
            */
            void reset_start(const long long _start_count) noexcept
            {
                start_count = _start_count;
            }
            /**
            *@brief 关于计数器比较的运算符
            *@param value:计数值
            *@tparam Type:比较类型
            */
            template <class Type>
            bool operator==(const Type value) const { static_assert(std::is_arithmetic_v<Type>,"Not support type of countercmp" ); return count == static_cast<long long>(value); }
            template <class Type>
            bool operator!=(const Type value) const { static_assert(std::is_arithmetic_v<Type>,"Not support type of countercmp" ); return count != static_cast<long long>(value); }
            template <class Type>
            bool operator>(const Type value) const { static_assert(std::is_arithmetic_v<Type>,"Not support type of countercmp" ); return count > static_cast<long long>(value); }
            template <class Type>
            bool operator<(const Type value) const { static_assert(std::is_arithmetic_v<Type>,"Not support type of countercmp" ); return count < static_cast<long long>(value); }
            template <class Type>
            bool operator>=(const Type value) const { static_assert(std::is_arithmetic_v<Type>,"Not support type of countercmp" ); return count >= static_cast<long long>(value); }
            template <class Type>
            bool operator<=(const Type value) const { static_assert(std::is_arithmetic_v<Type>,"Not support type of countercmp" ); return count <= static_cast<long long>(value); }

            bool operator==(const Counter &other) const { return count == other.count; }
            bool operator!=(const Counter &other) const { return count != other.count; }
            bool operator>(const Counter &other) const { return count > other.count; }
            bool operator<(const Counter &other) const { return count < other.count; }
            bool operator>=(const Counter &other) const { return count >= other.count; }
            bool operator<=(const Counter &other) const { return count <= other.count; }

            //++->return
            Counter& operator++()
            {
                ++count;
                return *this;
            }
            //return-> ++
            Counter operator++(int)
            {
                Counter temp = *this;
                ++count;
                return temp;
            }
            //-- ->return
            Counter& operator--()
            {
                --count;
                return *this;
            }
            //return-> --
            Counter operator--(int)
            {
                Counter temp = *this;
                --count;
                return temp;
            }

            template <class Type>
            Counter& operator+=(const Type value)
            {
                count += static_cast<long long>(value);
                return *this;
            }

            template <class Type>
            Counter& operator-=(const Type value)
            {
                count -= static_cast<long long>(value);
                return *this;
            }

            /**
            *@brief 重设所有计数器属性，包括默认值。
            *@note 计数器的记忆可以被消除，而我对她的记忆却不能...
            */
            void clear() noexcept
            {
                count = 0;
                start_count = 0;
            }

            /**
            *@brief 获取计数值
            *@return 返回该对象的计数值
            */
            long long get_count() const
            {
               return count;
            }
        };
    }
}

#endif