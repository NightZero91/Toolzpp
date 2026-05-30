#ifndef VECTORPP_H
#define VECTORPP_H
#include <iostream>
/**
 * @file vectorpp.h
 * @date 2026-05-01
 * @author NightZero91
 * @brief 简单的2，3，4维度向量
 * @warning 只提供声明功能，无子函数
 */
namespace tlz
{
    /**
    *@brief 不同维度的向量
    */
    namespace vec
    {
        template <class T>
        struct Vector2
        {
            T x, y;
        };

        template <class U>
        struct Vector3
        {
            U x, y, z;
        };

        template <class V>
        struct Vector4
        {
            V x, y, z, w;
        };
    }
    /**
    *@brief 向量运算符重载
    *@note 直接写入到输出对象
    */
    template <class T>
    std::ostream &operator<<(std::ostream &o, const tlz::vec::Vector2<T> &vec)
    {
        o << vec.x << " " << vec.y;
        return o;
    }

    template <class T>
    std::ostream &operator<<(std::ostream &o, const tlz::vec::Vector3<T> &vec)
    {
        o << vec.x << " " << vec.y << " " << vec.z;
        return o;
    }

    template <class T>
    std::ostream &operator<<(std::ostream &o, const tlz::vec::Vector4<T> &vec)
    {
        o << vec.x << " " << vec.y << " " << vec.z << " " << vec.w;
        return o;
    }
}

#endif