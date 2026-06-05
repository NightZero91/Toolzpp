#ifndef CARRAYPP_H
#define CARRAYPP_H
/**
 * @file carraypp.h
 * @date 2026-05-22
 * @author NightZero91
 * @brief 一个针对C数组的转换和算法模块，更好地使用C数组
 * @note 欢迎使用者对该文件提出任何建议
 */
#include <array>
#include <cstddef>
#include <iterator>
#include <stdexcept>
#include <type_traits>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <algorithm>
#include <numeric>

namespace tlz 
{
    namespace carraypp
    {

        /**
        *@brief C数组转换为现代的vector
        *@param carray C数组
        *@tparam T：数组类型
        *@tparam Size：数组大小 你没听错要手动传大小:(
        *@warning 请不要乱传大小，这会造成未定义行为，它的后果是不可预料的。害怕)
        *@note 我已经提前做好了C++35时写vector转其他奇怪容器的准备了，但那时写代码的人可能就不是我了XD(AI)
        *@note 有可能这段垃圾注释都会被AI删除。
        *@return 新std::vector<Type>
        */
        template<class T, size_t Size>
        std::vector<T> carray_to_vector(const T* const carray)
        {
            if (carray == nullptr) throw std::runtime_error("The array is a nullptr.");
            std::vector<T> result{};
            result.reserve(Size);
            std::copy(carray, carray + Size, std::back_inserter(result));
            return result;
        }
        /**
        *@brief C数组转换为现代的std::array
        *@param carray C数组
        *@tparam T：数组类型
        *@tparam Size：数组大小 你没听错要手动传大小:(
        *@warning 请不要乱传大小，这会造成未定义行为，它的后果是不可预料的。
        *@return 新std::array
        */
        template<class T, size_t Size>
        std::array<T, Size> carray_to_stdarray(const T* const carray)
        {
            if (carray == nullptr) throw std::runtime_error("The array is a nullptr.");
            std::array<T, Size> result{};
            std::copy(carray, carray + Size, result.begin());
            return result;
        }
        /**
        *@brief 两个C数组转unordered_map
        *@param karr：存有键的数组
        *@param varr：存有值的数组
        *@tparam K：键类型，V：值类型
        *@tparam Size：数组大小 两个数组的大小必须一样！！！
        *@warning 请不要乱传大小，这会造成未定义行为，它的后果是不可预料的。
        *@return 新unordered_map
        */
        template<class K, class V, size_t Size>
        std::unordered_map<K, V> carray_to_unordered_map(const K* karr, const V* varr)
        {
            if (karr == nullptr || varr == nullptr) throw std::runtime_error("The array is a nullptr.");
            if (Size == 0) throw std::runtime_error("Not support an empty array.");
            std::unordered_map<K, V> result{};
            result.reserve(Size);
            for (size_t i = 0; i < Size; ++i)
            {
                auto k = karr[i];
                auto v = varr[i];
                if (result.find(k) == result.end())
                    result[k] = v;
                else
                    throw std::runtime_error("It's has same key in karr.");
            }
            return result;
        }
        /**
        *@brief 用同一个值填满C数组
        *@param carray：C数组
        *@param value：值
        *@tparam T：数组类型，Size：数组大小 你没听错要手动传大小:(
        */
        template<class T, size_t Size>
        void reset_all(T* const carray, const T& value)
        {
            if (carray == nullptr) throw std::runtime_error("The array is a nullptr.");
            std::fill(carray, carray + Size, value);
        }
        /**
        *@brief 找到C数组的最大值
        *@param carray：C数组
        *@tparam T：数组类型，Size：数组大小 你没听错要手动传大小:(
        *@return 最大值
        */
        template<class T, size_t Size>
        T find_maxv(const T* const carray)
        {
            static_assert(std::is_arithmetic<T>::value,"The array type isn't arithmetic.");
            if (carray == nullptr) throw std::runtime_error("The array is a nullptr.");
            if (Size == 0) throw std::runtime_error("Not support an empty array.");
            return *std::max_element(carray, carray + Size);
        }
        /**
        *@brief 找到C数组的最大值
        *@param carray：C数组
        *@tparam T：数组类型，Size：数组大小 你没听错要手动传大小:(
        *@return 最小值
        */
        template<class T, size_t Size>
        T find_minv(const T* const carray)
        {
            static_assert(std::is_arithmetic<T>::value,"The array type isn't arithmetic.");
            if (carray == nullptr) throw std::runtime_error("The array is a nullptr.");
            if (Size == 0) throw std::runtime_error("Not support an empty array.");
            return *std::min_element(carray, carray + Size);
        }
        /**
        *@brief 检查C数组里面包不包含一个值
        *@param carray：C数组
        *@param value：值
        *@tparam T：数组类型，Size：数组大小 你没听错要手动传大小:(
        *@return 寻找的结果 true/false
        */
        template<class T, size_t Size>
        bool carray_contains(const T* const carray, const T& value)
        {
            if (carray == nullptr) throw std::runtime_error("The array is a nullptr.");
            if (Size == 0) throw std::runtime_error("Not support an empty array.");
            auto it = std::find(carray, carray + Size, value);
            return it != carray + Size;
        }
        /**
        *@brief 反转C数组
        *@param carray：C数组
        *@tparam T：数组类型，Size：数组大小 你没听错要手动传大小:(
        */
        template<class T, size_t Size>
        void carray_reverse(T* const carray)
        {
            if (carray == nullptr) throw std::runtime_error("The array is a nullptr.");
            if (Size == 0 || Size == 1) return;
            std::reverse(carray, carray + Size);
        }
        /**
        *@brief 打印C数组
        *@param carray：C数组
        *@tparam T：数组类型，Size：数组大小 你没听错要手动传大小:(
        */
        template<class T, size_t Size>
        void carray_print(const T* const carray)
        {
            std::cout << "[";
            for (size_t i = 0; i < Size; i++)
            {
                std::cout << carray[i];
                if (i != Size - 1) std::cout << ",";
            }
            std::cout << "]";
        }
        /**
        *@brief 求C数组所有元素的和
        *@param carray：C数组
        *@tparam T：数组类型，Size：数组大小 你没听错要手动传大小:(
        *@return 和
        *@warning T必须是数值类型
        */
        template<class T, size_t Size>
        T carray_sum(const T* const carray)
        {
            static_assert(std::is_arithmetic<T>::value,"The array type isn't arithmetic.");
            if (carray == nullptr) throw std::runtime_error("The array is a nullptr.");
            if (Size == 0) throw std::runtime_error("Not support an empty array.");
            auto sum = std::accumulate(carray, carray + Size, T{0});
            return sum;
        }
        /**
        * @brief 对C数组进行过滤
        * @tparam Func：lambda λ表达式，T：数组的类型， Size：数组大小 你没听错要手动传大小:(
        * @param carray：C数组
        * @param function 一个lambda λ表达式
        * @warning:lambda表达式必须返回bool，并且接受一个与vec类型相同的值
        * @return 返回一个vector而不是C数组
        */
        template<class T, class Func, size_t Size>
        std::vector<T> carray_filter(const T* const carray, Func&& function)
        {
            if (carray == nullptr) throw std::runtime_error("The array is a nullptr.");
            std::vector<T> result = {};
            result.reserve(Size);
            std::copy_if(carray, carray + Size, std::back_inserter(result), function);
            return result;
        }
        /**
        * @brief 对C数组进行映射
        * @tparam Func：lambda λ表达式，T：数组的类型， Size：数组大小 你没听错要手动传大小:(
        * @param carray：C数组
        * @param function 一个lambda λ表达式
        * @warning:lambda表达式遵守std::transform要求的样式
        * @return 返回一个vector而不是C数组
        * @note 指定的lambda函数就像不同的性格爱好,这个文件里的函数就像人
        * 不同人有不同的所感所爱。我想说的是,人要活出独一无二的自己.
        */
        template<class T, class Func, size_t Size>
        std::vector<T> carray_map(const T* const carray, Func&& function)
        {
            if (carray == nullptr) throw std::runtime_error("The array is a nullptr.");
            std::vector<T> result = {};
            result.reserve(Size);  
            std::transform(carray, carray + Size, std::back_inserter(result), function);
            return result;
        }
    }
}

#endif