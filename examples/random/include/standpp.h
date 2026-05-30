#ifndef STANDERPP_H
#define STANDERPP_H
/**
 * @file standpp.h
 * @date 2026-05-15
 * @author NightZero91
 * @brief 一个"代表"类，用于表示一组允许的值，提供成员检查功能
 * @note 欢迎使用者对该文件提出任何建议
 * @warning 多线程请确保加锁
 */
#include <algorithm>
#include <stdexcept>
#include <vector>

namespace tlz 
{
    namespace stand 
    {
        /**
        *@brief 代表类
        *@tparam 代表数据类型
        */
        template <class Type> 
        class Stand 
        {
        private:
            //数据
            std::vector<Type> stand_data;
        public:
            Stand() = delete;
            /**
            *@brief 构造一个代表类
            *@param vec：代表数据
            */
            explicit Stand(const std::vector<Type> &vec) : stand_data(vec) {}
            /**
            *@brief 验证一个值是否包含在代表中
            *@param value 要查验的值
            */
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
            /**
            *@brief 验证一个值是否包含在代表中
            *@param value 要查验的值
            */
            friend bool operator==(const Type &value, const Stand<Type> &stand) 
            {
                return (stand == value);
            }
            /**
            *@brief 重设整个代表数据
            *@param vec 新代表数据
            */
            void reset(const std::vector<Type> &vec) { stand_data = vec; }
            /**
            *@brief 添加代表值
            *@param value 要添加的值
            */
            void add_stand(const Type &value) { stand_data.push_back(value); }
            /**
            *@brief 移除代表值
            *@param value 要移除的值
            */
            void remove(const Type &value) 
            {
                auto it = std::find(stand_data.begin(), stand_data.end(), value);
                if (it != stand_data.end()) 
                {
                    stand_data.erase(it);
                }
            }
            /**
            *@brief 设置代表值
            *@param value 要设置的值
            *@param idx 要设置的值的索引
            */
            void set(const size_t idx, const Type &value) 
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
            /**
            *@brief 检测代表是否为空
            *@return 检查结果
            */
            bool is_empty() const noexcept { return stand_data.empty(); }
            /**
            *@brief 获取代表值
            *@param idx 要获取的值的索引
            */
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