#ifndef RANDOMPP_H
#define RANDOMPP_H
/**
* @file randompp.h
* @date 2026-05-01
* @author NightZero91
* @brief 非常方便的random随机数生成器
* @note 欢迎使用者对该文件提出任何建议
* @note 这个世界是本就是随机的，但我们的相遇确是命中注定.
* @warning 多线程注意加锁哦
*/
#include <random>
#include <vector>

namespace tlz
{
    namespace random
    {
        /**
        *@brief 随机数生成器
        */
        class Randomer
        {
        private:
            std::random_device rd;
            std::mt19937 rng;
        public:
            Randomer() : rd() , rng(rd())
            {}
            //禁用拷贝和移动
            Randomer(const Randomer &) = delete;
            Randomer &operator=(const Randomer &) = delete;
            Randomer(Randomer &&) = delete;
            Randomer &operator=(Randomer &&) = delete;
            /**
            *@brief 如同python般的randint
            *@param min：最小值
            *@param max：最大值
            */
            int randint(int min, int max)
            {
                if (min > max) throw std::invalid_argument("The min arg cannot > max.");
                std::uniform_int_distribution<int> dist(min, max);
                return dist(rng);
            }
            /**
            *@brief 随机实数
            *@param min：最小值
            *@param max：最大值
            */
            double randreal(double min, double max)
            {
                if (min > max) throw std::invalid_argument("The min arg cannot > max.");
                std::uniform_real_distribution<double> dist(min, max);
                return dist(rng);
            }
            /**
            *@brief 在向量中随机抽选一个值
            *@param vec：向量数据
            */
            template <class _Type>
            _Type choice(const std::vector<_Type> &vec)
            {
                if (vec.empty())
                {
                    throw std::runtime_error("vec cannot be empty! ");
                }
                auto size = vec.size();
                std::uniform_int_distribution<int> dist(0, size - 1);
                _Type res = vec[dist(rng)];
                return res;
            }
        };
    }
}

#endif