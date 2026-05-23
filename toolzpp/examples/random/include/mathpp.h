#ifndef MATHPP_H
#define MATHPP_H
//@--mathpp--toolzpp
//260501
#include <cstddef>
#include <stdexcept>
#include <vector>
#include "vectorpp.h"
#include <functional>
#include <cmath>
#include <iostream>
#include <type_traits>
#include <algorithm>
#include <unordered_map>


namespace tlz
{
    namespace math
    {
        template<class T>
        T vector_sum(const std::vector<T> &vec)
        {
            static_assert(std::is_arithmetic_v<T>, "T must be arithmetic type");
            T sum{};
            for (const auto &i : vec)
            {
                sum += i;
            }
            return sum;
        }

        template <class T>
        double average(const std::vector<T> &vec)
        {
            static_assert(std::is_arithmetic_v<T>, "T must be arithmetic type");
            if (vec.empty())
                return 0.0;

            double sum = 0.0;

            for (auto &i : vec)
                sum += static_cast<double>(i);

            double res = sum / vec.size();
            return res;
        }
        //the weight CAN < 0
        template<class T, class U>
        double average(const std::vector<T>& data, const std::vector<U>& weights)
        {
            static_assert(std::is_arithmetic_v<T>, "T/U must be arithmetic type");    
            if (data.size() != weights.size()) throw std::runtime_error("The data.size() and the weights.size() must be same.");
            if (data.empty())
                return 0.0;
            double sum = 0.0;
            for (size_t i = 0; i < data.size(); i++)
            {
                sum += static_cast<double>(data[i]) * static_cast<double>(weights[i]);
            }
            auto weights_sum = vector_sum(weights);
            if (std::abs(weights_sum) < 1e-12) throw std::runtime_error("The sum of weights cannot be 0");
            double res = sum / weights_sum;
            return res;
        }

        template<class T>
        double median(const std::vector<T>& data)
        {
            static_assert(std::is_arithmetic<T>::value, "T must be arithmetic type.");
            if (data.empty()) throw std::runtime_error("The vec cannot empty.");
            std::vector<T>vec = data;
            std::sort(vec.begin(), vec.end());
            double res{};
            if (vec.size() % 2 == 0)
            {
                res = (static_cast<double>(vec[vec.size() / 2 - 1]) + static_cast<double>(vec[vec.size() / 2])) / 2;
            }
            else
            {
                res = static_cast<double>(vec[vec.size() / 2]);
            }
            return res;
        }

        template<class T>
        T mode(const std::vector<T>& data)
        {
            static_assert(std::is_arithmetic<T>::value, "T must be arithmetic type.");
            if (data.empty()) throw std::runtime_error("The vec cannot empty.");
            std::unordered_map<T, size_t> map;
            for (const auto& i : data)
            {
                if (map.find(i) == map.end())
                {
                    map[i] = 1;
                }
                else 
                {
                    map[i]++;
                }
            }
            std::pair<T, size_t> max{};
            for (const auto &pair : map)
            {
                if (pair.second > max.second)
                    max = pair;
            }
            return max.first;
        }

        template <class T, class U>
        double point_distance(const vec::Vector2<T> &sou, const vec::Vector2<U> &dst)
        {
            const double x_1 = static_cast<double>(sou.x);
            const double y_1 = static_cast<double>(sou.y);

            const double x_2 = static_cast<double>(dst.x);
            const double y_2 = static_cast<double>(dst.y);

            double distance = sqrt((pow((x_1 - x_2), 2) + (pow((y_1 - y_2), 2))));
            return distance;
        }

        template <class X, class Y>
        class FunctionPack
        {
        private:
            std::vector<std::pair<X, Y>> pack;
        public:
            FunctionPack() = delete;
            //防止隐式转换
            explicit FunctionPack(std::vector<std::pair<X,Y>> vec) : pack(std::move(vec)){}
            friend std::ostream& operator<<(std::ostream& o, const FunctionPack& fpack)
            {
                for (auto i : fpack.pack)
                {
                    o << "x=" << i.first << "," << "y=" << i.second << "\n";
                }
                return o;
            }
            std::vector<X> only_x() const
            {
                std::vector<X> res;
                for (auto i : pack)
                {
                    res.push_back(i.first);
                }
                return res;
            }
            std::vector<Y> only_y() const
            {
                std::vector<Y> res;
                for (auto i : pack)
                {
                    res.push_back(i.second);
                }
                return res;
            }
            std::vector<std::pair<X, Y>> get_pack() const noexcept
            {
                return pack;
            }
        };

        template <class In, class Out>
        class MathFunction
        {
        private:
            //返回值
            std::function<Out(In)> func;
        public:
            MathFunction() = delete;
            //构造
            explicit MathFunction(std::function<Out(In)> _func) : func(std::move(_func)) {}
            //重载
            Out operator()(const In &value) const
            {
                return func(value);
            }
            void reset(std::function<Out(In)>& _func)
            {
                this->func = std::move(_func);
            }
        };
        template <class In, class Out>
        FunctionPack<In, Out>sample(const MathFunction<In, Out>& f, In start, size_t count, In step = 1)
        {
            std::vector<std::pair<In, Out>>vec;
            //预分配
            vec.reserve(count);
            for (size_t i = 0; i < count; ++i)
            {
                vec.emplace_back(start, f(start));
                start += step;
            }
            //移动vec
            return FunctionPack<In, Out>(std::move(vec));
        }
    }
}

#endif