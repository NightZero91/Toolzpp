#ifndef ALGOPP_H
#define ALGOPP_H
/**
 * @file algopp.h
 * @date 2026-05-05
 * @author NightZero91
 * @brief 一个简化一些STL算法的文件，能使常用的操作调用的更加直接
 * @note 欢迎使用者对该文件提出任何建议
 */
#include <stdexcept>
#include <vector>
#include <algorithm>
namespace tlz
{
    namespace algo
    {
        /**
        * @brief 对向量进行映射[1,2,3,4] -> [2,4,6,8]
        * @tparam Func:lambda λ表达式，T:向量的类型
        * @param vec:向量
        * @param function 一个lambda λ表达式
        * @warning:lambda表达式遵守std::transform要求的样式
        * @return 返回原来vec的引用
        * @note 指定的lambda函数就像不同的性格爱好,这个文件里的函数就像人
        * 不同人有不同的所感所爱。我想说的是,人要活出独一无二的自己.
        */
        template<class Func, class T>
        std::vector<T>& vector_map(std::vector<T>& vec, Func&& function)
        {
            if (vec.empty()) return vec;
            std::transform(vec.begin(), vec.end(), vec.begin(), function);
            return vec;
        }
        /**
        * @brief 对向量进行过滤
        * @tparam Func:lambda λ表达式，T:向量的类型
        * @param vec:向量
        * @param function 一个lambda λ表达式
        * @warning:lambda表达式必须返回bool，并且接受一个与vec类型相同的值
        * @return 返回原来vec的引用
        */
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
        /**
        * @brief 对向量切片
        * @tparam Type:向量的类型
        * @param vec:向量
        * @param min_idx:最小索引
        * @param max_idx:最大索引
        * @return 返回新vector
        */
        template<class Type>
        std::vector<Type> vector_slice(const std::vector<Type> &vec, size_t min_idx, size_t max_idx)
        {
            if (min_idx > max_idx) throw std::invalid_argument("The arg min cannot > max");
            if (max_idx >= vec.size()) throw std::out_of_range("The arg max out of range!");
            std::vector<Type> result{};

            for (size_t i = min_idx; i <= max_idx; ++i)
            {
                result.push_back(vec[i]);
            }
            return result;
        }
        /**
        * @brief 查找向量是否有一个元素
        * @tparam Type:向量的类型
        * @param vec:向量
        * @param thing:要查找的内容
        */
        template <class Type>
        bool contains(const std::vector<Type> &vec, const Type thing)
        {
            return (std::find(vec.begin(), vec.end(), thing) != vec.end());
        }
    }
    /**
    *@brief 如同python的运算符重载，实现向量重复
    *@tparam Type:向量的类型
    *@param vec:原向量
    *@param count:重复的次数
    *@return 新的向量
    */
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
    /**
    *@brief 如同python的运算符重载，实现向量重复
    *@tparam Type:向量的类型
    *@param vec:原向量
    *@param count:重复的次数
    *@return 新的向量
    */
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
    /**
    *@brief 如同python的运算符重载，实现向量相加
    *@tparam Type:向量的类型
    *@param vec:向量甲
    *@param other:向量乙
    *@return 新的向量
    */
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