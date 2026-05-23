#ifndef RANDOMPP_H
#define RANDOMPP_H
//--randompp--toolzpp
//260505
#include <random>
#include <algorithm>
#include <vector>
#include <stdexcept>
#include <stdexcept>

namespace tlz
{
    namespace random
    {
        class Randomer
        {
        private:
            std::random_device rd;
            std::mt19937 rng;
        public:
            Randomer() : rd() , rng(rd())
            {}
            //🈲止拷贝
            Randomer(const Randomer &) = delete;
            Randomer &operator=(const Randomer &) = delete;
            Randomer(Randomer &&) = delete;
            Randomer &operator=(Randomer &&) = delete;
            //实现整形随机数
            int randint(int min, int max)
            {
                if (min > max) throw std::invalid_argument("The min arg cannot > max.");
                std::uniform_int_distribution<int> dist(min, max);
                return dist(rng);
            }

            double randreal(double min, double max)
            {
                if (min > max)
                {
                    std::swap(min, max);
                }
                std::uniform_real_distribution<double> dist(min, max);
                return dist(rng);
            }
            
            template <class _Type>
            _Type choice(std::vector<_Type> &vec)
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

            ~Randomer()
            {
            }
        };
    }
}

#endif