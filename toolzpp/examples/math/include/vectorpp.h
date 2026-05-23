#ifndef VECTORPP_H
#define VECTORPP_H
#include <iostream>
//--vectorpp--toolzpp
//260505
namespace tlz
{
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
}

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

#endif