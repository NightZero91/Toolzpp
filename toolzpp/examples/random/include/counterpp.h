#ifndef COUNTERPP_H
#define COUNTERPP_H
//@--counterpp--toolzpp
//260515
namespace tlz
{
    namespace counter
    {
        class Counter
        {
        private:
            long long count;
            long long start_count;
        public:
            Counter() : count(0), start_count(0) {};
            Counter(long long _count, long long _start_count) : count(_count), start_count(_start_count) {};
            ~Counter() = default;

            //重设计数器
            void reset(const long long _count)
            {
                count = _count;
            }

            //无参重设计数器
            void reset()
            {
                count = start_count;
            }

            //重设默认计数值
            void reset_start(const long long _start_count)
            {
                start_count = _start_count;
            }
            //比较计数值
            template <class Type>
            bool operator==(const Type value) const { return count == static_cast<long long>(value); }
            template <class Type>
            bool operator!=(const Type value) const { return count != static_cast<long long>(value); }
            template <class Type>
            bool operator>(const Type value) const { return count > static_cast<long long>(value); }
            template <class Type>
            bool operator<(const Type value) const { return count < static_cast<long long>(value); }
            template <class Type>
            bool operator>=(const Type value) const { return count >= static_cast<long long>(value); }
            template <class Type>
            bool operator<=(const Type value) const { return count <= static_cast<long long>(value); }

            //自增
            Counter& operator++()
            {
                ++count;
                return *this;
            }

            Counter operator++(int)
            {
                Counter temp = *this;
                ++count;
                return temp;
            }
            //加减固定值
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

            //全部初始化
            void clear()
            {
                count = 0;
                start_count = 0;
            }

            //getter&seter
            template <class Type>
            void set_count(const Type _count)
            {
                count = static_cast<long long>(_count);
            }

            long long get_count() const
            {
               return count;
            }
        };
    }
}

#endif