#ifndef STANDERPP_H
#define STANDERPP_H
//@--standpp--toolzpp
//260515
#include <vector>
#include <stdexcept>
namespace tlz
{
    namespace stand
    {
        template <class Type>
        //代表类
        class Stand
        {
        private:
            std::vector<Type> stand_data;
        public:
            Stand() = delete;
            explicit Stand(const std::vector<Type>& vec) : stand_data(vec) {}
            //检查对应元素是否在一个代表里
            bool operator==(const Type &value) const
            {
                for (auto &v : stand_data)
                {
                    if (v == value)
                    {
                        return true;
                    }
                }
                return false;
            }
            //检查对应元素是否在一个代表里
            friend bool operator==(const Type &value, const Stand<Type>& stand)
            {
                return (stand == value);
            }
            //重设代表所对应的数据
            void reset(const std::vector<Type> &vec)
            {
                stand_data = vec;
            }
            //添加代表值
            void add_stand(const Type &value)
            {
                stand_data.push_back(value);
            }
            //溢出代表值
            void remove(const Type &value)
            {
                auto it = std::find(stand_data.begin(), stand_data.end(), value);
                if (it != stand_data.end())
                {
                    stand_data.erase(it);
                }
            }
            //设置对应的代表值
            void set(const size_t idx, const Type& value)
            {
                if (idx < stand_data.size())
                {
                    stand_data[idx] = value;
                }
                else
                {
                    throw std::out_of_range("The arg1 is out of range!");
                }
            }
            //判断是否为空
            bool is_empty() const
            {
                return stand_data.empty();
            }
            //获取对应代表值
            Type get(const size_t idx) const
            {
                if (idx < stand_data.size())
                {
                    return stand_data[idx];
                }
                else
                {
                    throw std::out_of_range("The arg1 is out of range!");
                }
            }
        };
    }
}

#endif