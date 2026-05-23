#ifndef NUM_H
#define NUM_H

#include <iostream>
// Num
namespace pp
{
    namespace num
    {
        template <class T>
        class Num
        {
        private:
            T value;

        public:
            Num() : value(0)
            {
            }

            // 通用构造函数
            template <typename U>
            Num(const U &var) : value(static_cast<T>(var))
            {
            }

            // 只读方法必须加 const
            T get_value() const
            {
                return value;
            }

            template <class U>
            Num<T>& set_value(const U &var)
            {
                this->value = static_cast<T>(var);
                return *this;
            }

            template <class U>
            Num(const Num<U> &other) : value(static_cast<T>(other.get_value())) {}

            template <class U>
            Num(Num<U> &&other)
            {
                this->value = static_cast<T>(other.get_value());
                other.set_value(0);
            }

            template <class U>
            Num &operator=(const Num<U> &other)
            {
                this->value = other.get_value();
                return *this;
            }
            template <class U>
            Num &operator=(Num<U> &&other)
            {
                this->value = static_cast<T>(other.get_value());
                other.set_value(0);
                return *this;
            }

            // 赋值
            template <class U>
            Num &operator=(const U &var)
            {
                value = static_cast<T>(var);
                return *this;
            }

            // 四则运算：必须用 const &，否则临时对象不能运算

            template <class U>
            Num<T> operator+(const Num<U> &other) const
            {
                return Num(static_cast<T>(this->value + other.get_value()));
            }

            template <class U>
            Num<T> operator-(const Num<U> &other) const
            {
                return Num(static_cast<T>(this->value - other.get_value()));
            }

            template <class U>
            Num<T> operator*(const Num<U> &other) const
            {
                return Num(static_cast<T>(this->value * other.get_value()));
            }

            template <class U>
            Num<T> operator/(const Num<U> &other) const
            {
                if (other.get_value() == 0) throw std::runtime_error("cannot devide by '0'.");
                return Num(static_cast<T>(this->value / other.get_value()));
            }

            // 复合赋值
            template <class U>
            Num<T> &operator+=(const Num<U> &other)
            {
                this->value += static_cast<T>(other.value);
                return *this;
            }

            template <class U>
            Num<T> &operator-=(const Num<U> &other)
            {
                this->value -= static_cast<T>(other.value);
                return *this;
            }

            template <class U>
            Num<T> &operator*=(const Num<U> &other)
            {
                this->value *= static_cast<T>(other.value);
                return *this;
            }

            template <class U>
            Num<T> &operator/=(const Num<U> &other)
            {
                if (other.get_value() == 0) throw std::runtime_error("cannot devide by '0'.");
                this->value /= static_cast<T>(other.value);
                return *this;
            }

            template <class U>
            bool operator>(const Num<U> &other) const { return this->get_value() > other.get_value(); }
            template <class U>
            bool operator<(const Num<U> &other) const { return this->get_value() < other.get_value(); }
            template <class U>
            bool operator==(const Num<U> &other) const { return this->get_value() == other.get_value(); }
            template <class U>
            bool operator>=(const Num<U> &other) const { return this->get_value() >= other.get_value(); }
            template <class U>
            bool operator<=(const Num<U> &other) const { return this->get_value() <= other.get_value(); }

            // 输出流：只需要一个 const & 版本，能同时处理左值/右值
            template <class U>
            friend std::ostream &operator<<(std::ostream &o, const Num<U> &num)
            {
                o << num.get_value();
                return o;
            }

            template<class U>
            Num<T>& change()
            {
                this->value = static_cast<T>(static_cast<U>(this->get_value()));
                return *this;
            }

            template<class U>
            void swap(const Num<U>& other)
            {
                auto tmp = value;
                value = other.get_value();
                other.set_value(tmp);
            }

            ~Num() {}
        };

        // 类型转换工具函数（统一用 const &，支持临时对象）
        template <class T, class U>
        Num<T> change(const Num<U> &other)
        {
            return Num<T>(static_cast<T>(other.get_value()));
        }
    }
    using int_pp = num::Num<int>;
    using float_pp = num::Num<float>;
    using double_pp = num::Num<double>;
}

#endif