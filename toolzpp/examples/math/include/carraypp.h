#ifndef CARRAYPP_H
#define CARRAYPP_H
//@carraypp--toolzpp
//260522
#include <array>
#include <cstddef>
#include <stdexcept>
#include <type_traits>
#include <vector>
#include <unordered_map>
#include <iostream>

namespace tlz 
{
    namespace carraypp
    {
        template<class T, size_t Size>
        std::vector<T> carray_to_vector(const T* const carray)
        {
            if (carray == nullptr) throw std::runtime_error("The array is a nullptr.");
            std::vector<T> result{};
            result.reserve(Size);
            for (size_t i = 0; i < Size; i++)
            {
                result.push_back(carray[i]);
            }
            return result;
        }

        template<class T, size_t Size>
        std::array<T, Size> carray_to_stdarray(const T* const carray)
        {
            if (carray == nullptr) throw std::runtime_error("The array is a nullptr.");
            std::array<T, Size> result{};
            for (size_t i = 0; i < Size; i++)
            {
                result[i] = carray[i];
            }
            return result;
        }

        template<class K, class V, size_t Size>
        std::unordered_map<K, V> carray_to_unordered_map(const K* karr, const V* varr)
        {
            if (karr == nullptr || varr == nullptr) throw std::runtime_error("The array is a nullptr.");
            std::unordered_map<K, V> result{};
            result.reserve(Size);
            for (size_t i = 0; i < Size; i++)
            {
                auto k = karr[i];
                auto v = varr[i];
                result[k] = v;
            }
            return result;
        }

        template<class T, size_t Size>
        void reset_all(T* const carray, const T& value)
        {
            if (carray == nullptr) throw std::runtime_error("The array is a nullptr.");
            for (size_t i = 0; i < Size; i++)
            {
                carray[i] = value;
            }
        }

        template<class T, size_t Size>
        T find_maxv(const T* const carray)
        {
            if (carray == nullptr) throw std::runtime_error("The array is a nullptr.");
            if (Size == 0) throw std::runtime_error("Not support an empty array.");
            static_assert(std::is_arithmetic<T>::value,"The array type isn't arithmetic.");
            T max = carray[0];
            for (size_t i = 0; i < Size; i++)
            {
                if (carray[i] > max) max = carray[i];
            }
            return max;
        }

        template<class T, size_t Size>
        T find_minv(const T* const carray)
        {
            if (carray == nullptr) throw std::runtime_error("The array is a nullptr.");
            if (Size == 0) throw std::runtime_error("Not support an empty array.");
            static_assert(std::is_arithmetic<T>::value,"The array type isn't arithmetic.");
            T min = carray[0];
            for (size_t i = 0; i < Size; i++)
            {
                if (carray[i] < min) min = carray[i];
            }
            return min;
        }

        template<class T, size_t Size>
        bool carray_contains(const T* const carray, const T& value)
        {
            if (carray == nullptr) throw std::runtime_error("The array is a nullptr.");
            if (Size == 0) return false;
            for (size_t i = 0; i < Size; i++)
            {
                if (carray[i] == value) return true;
            }
            return false;
        }

        template<class T, size_t Size>
        void carray_reverse(T* const carray)
        {
            if (carray == nullptr) throw std::runtime_error("The array is a nullptr.");
            if (Size == 0 || Size == 1) return;
            for (size_t i = 0; i < Size / 2; i++)
            {
                T tmp = carray[i];
                carray[i] = carray[Size - 1 - i];
                carray[Size - 1 - i] = tmp;
            }
        }

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
    }
}

#endif