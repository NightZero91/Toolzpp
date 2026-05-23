#ifndef ALGOPP_H
#define ALGOPP_H
//@--algopp--toolzpp
//260515
#include <cstddef>
#include <stdexcept>
#include <vector>
#include <algorithm>
namespace tlz
{
    namespace algo
    {
        //the function of arg and retrun value [must] be same
        template<class Func, class T>
        std::vector<T>& vector_map(std::vector<T>& vec, Func&& function)
        {
            for (auto &i : vec)
            {
                i = function(i);
            }
            return vec;
        }
        //the arg function [must] return a bool value.
        template <class Func, class T>
        std::vector<T>& vector_filter(std::vector<T>& vec, Func&& function)
        {
            for (auto p = vec.begin(); p != vec.end(); )
            {
                if (!function(*p))
                {
                    p = vec.erase(p);
                    continue;
                }
                ++p;
            }
            return vec;
        }

        template<class Type>
        std::vector<Type> vector_slice(const std::vector<Type> &vec, size_t min_idx, size_t max_idx)
        {
            if (min_idx > max_idx) throw std::invalid_argument("The arg min cannot > max");
            if (max_idx >= vec.size()) throw std::out_of_range("The arg max out of range!");
            std::vector<Type> result{};

            for (size_t i = min_idx; i <= max_idx; i++)
            {
                result.push_back(vec[i]);
            }
            return result;
        }

        template <class Type>
        bool contains(const std::vector<Type> &vec, const Type thing)
        {
            return (std::find(vec.begin(), vec.end(), thing) != vec.end());
        }
    }
    template <class Type>
    std::vector<Type> operator*(const std::vector<Type> &vec, const unsigned int count)
    {
        if (vec.empty() || count == 0)
        {
            return {};
        }
        size_t new_size = vec.size() * count;
        std::vector<Type> new_vec;
        new_vec.reserve(new_size);

        for (size_t i = 0; i < count; ++i)
        {
            for (auto j : vec)
            {
                new_vec.push_back(j);
            }
        }

        return new_vec;
    }

    template <class Type>
    std::vector<Type> operator*(const unsigned int count, const std::vector<Type> &vec)
    {
        if (vec.empty() || count == 0)
        {
            return {};
        }
        size_t new_size = vec.size() * count;
        std::vector<Type> new_vec;
        new_vec.reserve(new_size);

        for (size_t i = 0; i < count; ++i)
        {
            for (auto j : vec)
            {
                new_vec.push_back(j);
            }
        }

        return new_vec;
    }

    template <class Type>
    std::vector<Type> operator+(const std::vector<Type> &vec, const std::vector<Type> &other)
    {
        size_t new_size = vec.size() + other.size();
        std::vector<Type> new_vec;
        new_vec.reserve(new_size);

        for (auto i : vec)
            new_vec.push_back(i);

        for (auto j : other)
            new_vec.push_back(j);

        return new_vec;
    }
}

#endif