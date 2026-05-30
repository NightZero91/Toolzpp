#ifndef MATHPP_H
#define MATHPP_H
/**
 * @file mathpp.h
 * @date 2026-05-01
 * @author NightZero91
 * @brief 装有多个数学方法的文件
 * @note 欢迎使用者对该文件提出任何建议
 * @warning 多线程请确保加锁
 */
#include <stdexcept>
#include <vector>
#include "vectorpp.h"
#include <functional>
#include <cmath>
#include <iostream>
#include <type_traits>
#include <algorithm>
#include <unordered_map>
#include <numeric>

namespace tlz
{
    namespace math
    {
        /**
        *@brief 计算平均值
        *@param vec：数据
        *@tparam T：数据类型
        *@return 平均值
        */
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
        /**
        *@brief 计算加权平均值
        *@param data：数据
        *@tparam T：数据类型
        *@return 加权平均值
        *@note 权的长度必须和数据的长度相同，1对1
        */
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
            auto weights_sum = std::accumulate(data.begin(), data.end(), T{0});
            if (std::abs(weights_sum) < 1e-12) throw std::runtime_error("The sum of weights cannot be 0");
            double res = sum / weights_sum;
            return res;
        }
        /**
        *@brief 计算中位数
        *@param data：数据
        *@tparam T：数据类型
        *@return 中位数
        */
        template<class T>
        double median(const std::vector<T>& data)
        {
            static_assert(std::is_arithmetic_v<T>, "T must be arithmetic type.");
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
        /**
        *@brief 计算众数
        *@param data：数据
        *@tparam T：数据类型
        *@return 众数
        */
        template<class T>
        T mode(const std::vector<T>& data)
        {
            static_assert(std::is_arithmetic_v<T>, "T must be arithmetic type.");
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
                    ++map[i];
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
        /**
        *@brief 计算两点的距离
        *@param sou：点甲
        *@param dst：点乙
        */
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
        /**
        *@brief 函数批量执行后返回的包
        */
        template <class X, class Y>
        class FunctionPack
        {
        private:
            std::vector<std::pair<X, Y>> pack;
        public:
            FunctionPack() = delete;
            /**
            *@brief 构造包
            *@param vec：包pair<X,Y>
            */
            explicit FunctionPack(std::vector<std::pair<X,Y>> vec) : pack(std::move(vec)){}
            /**
            *@brief 输出这个包
            */
            friend std::ostream& operator<<(std::ostream& o, const FunctionPack& fpack)
            {
                for (auto i : fpack.pack)
                {
                    o << "x=" << i.first << "," << "y=" << i.second << "\n";
                }
                return o;
            }
            /**
            *@brief 解包：只剩自变量
            *@return 一个带自变量的vector
            */
            std::vector<X> only_x() const
            {
                std::vector<X> res;
                for (auto i : pack)
                {
                    res.push_back(i.first);
                }
                return res;
            }
            /**
            *@brief 解包：只剩函数值
            *@return 一个带函数值的vector
            */
            std::vector<Y> only_y() const
            {
                std::vector<Y> res;
                for (auto i : pack)
                {
                    res.push_back(i.second);
                }
                return res;
            }
            /**
            *@brief 获取整个包的原型
            *@return 一个装有自变量和函数值的vector<pair<X, Y>>
            */
            std::vector<std::pair<X, Y>> get_pack() const noexcept
            {
                return pack;
            }
        };
        /**
        *@brief 一个数学函数包装器
        *@tparam In：自变量类型，Out：函数值类型
        */
        template <class In, class Out>
        class MathFunction
        {
        private:
            std::function<Out(In)> func;
        public:
            MathFunction() = delete;
            /**
            *@brief 构造对象
            *@param _func 一个std::funtion
            */
            explicit MathFunction(std::function<Out(In)> _func) : func(std::move(_func)) {}
            /**
            *@brief 调用这个包装器的重载
            */
            Out operator()(const In &value) const
            {
                return func(value);
            }
            /**
            *@brief 重设这个包装器所指向的函数
            *@param _func：函数
            */
            void reset(std::function<Out(In)>& _func)
            {
                func = std::move(_func);
            }
        };
        /**
        *@brief 实现函数采样
        *@param f：函数包装器
        *@param start：采样起始点
        *@param count：采样次数
        *@param step：采样步长
        *@return 一个结果函数包
        */
        template <class In, class Out>
        FunctionPack<In, Out>sample(const MathFunction<In, Out>& f, In start, size_t count, In step = 1)
        {
            std::vector<std::pair<In, Out>>vec;
            vec.reserve(count);
            for (size_t i = 0; i < count; ++i)
            {
                vec.emplace_back(start, f(start));
                start += step;
            }
            return FunctionPack<In, Out>(std::move(vec));
        }
    }
}

#endif