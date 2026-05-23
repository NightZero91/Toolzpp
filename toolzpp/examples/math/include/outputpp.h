#ifndef OUTPUTPP_H
#define OUTPUTPP_H
//--outputpp--toolzpp
//260505
#include <iostream>
#include <vector>

namespace tlz
{
    template <class Type>
    std::ostream& operator<<(std::ostream& o, const std::vector<Type>& vec)
    {
        o << "[";

        // 遍历，不打印最后多余逗号
        bool first = true;
        for (const auto& elem : vec) {
            if (!first) {
                o << ",";
            }
            o << elem;
            first = false;
        }

        o << "]";
        return o;
    }
}


#endif