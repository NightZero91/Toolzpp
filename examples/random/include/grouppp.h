#ifndef GROUPPP_H
#define GROUPPP_H
/**
 * @file grouppp.h
 * @date 2026-05-15
 * @author NightZero91
 * @brief 一个存有多种属性的组，底层是unordered_map
 * @note 欢迎使用者对该文件提出任何建议
 * @warning 多线程请确保加锁
 */
#include <string>
#include <vector>
#include <unordered_map>
#include <stdexcept>

namespace tlz
{
    /**
    *@brief bool特化的逻辑检查方式(与，或，反)
    */
    enum CheckState
    {
        CS_AND,
        CS_OR,
        CS_FILP
    };

    namespace group
    {
        /**
        *@brief 一个id对应一个属性
        *@tparam V：属性类型
        */
        template<class V>
        class Group
        {
        private:
            std::unordered_map<std::string, V> data;
        public:
            Group(){};
            ~Group(){};
            /**
            *@brief 添加属性
            *@param id：属性id
            *@param value：属性值
            */
            void add(const std::string &id, V value)
            {
                if (data.find(id) != data.end())
                {
                    throw std::runtime_error("The value '" + id + "' is added do not readd!");
                }
                data[id] = value;
            }
            /**
            *@brief 重设已有属性
            *@param id：属性id
            *@param value：属性值
            *@note 找不到抛异常
            */
            void reset(const std::string &id, V value)
            {
                if (data.find(id) == data.end())
                {
                    throw std::runtime_error("The value '" + id + "' not found.");
                }
                data[id] = value;
            }
            /**
            *@brief 获取group大小
            *@return data的size
            */
            size_t size() const noexcept
            {
                return data.size();
            }
            /**
            *@brief 设置所有属性为一个值
            *@param value：值
            */
            void set_all(V value) noexcept
            {
                if (data.empty())
                {
                    return;
                }
                for (auto p = data.begin(); p != data.end(); ++p)
                {
                    p->second = value;
                }
            }
            /**
            *@brief 获取某个id的值
            *@param id：属性id
            *@return 对应属性值
            */
            V get(const std::string &id) const
            {
                if (data.find(id) == data.end())
                {
                    throw std::runtime_error("The value '" + id + "' not found.");
                }
                return data[id];
            }
            /**
            *@brief 判断组是否为空
            *@return data.empty返回的bool
            */
            bool is_empty() const
            {
                return data.empty();
            }
            /**
            *@brief 获取所有id
            *@return 一个vector，装有所有id
            */
            std::vector<std::string> get_id() const
            {
                std::vector<std::string> vec;
                vec.reserve(data.size());
                for (auto &k : data)
                {
                   vec.push_back(k.first); 
                }
                return vec;
            }
            /**
            *@brief 删除对应属性
            *@param id：属性id
            */
            void remove(const std::string &id)
            {
                auto it = data.find(id);
                if (it != data.end())
                {
                    data.erase(it);
                }
                else throw std::runtime_error("Cannot find the ID.");
            }
        };
        /**
        *@brief group的bool特化，管理大量bool
        */
        template<>
        class Group<bool>
        {
        private:
            std::unordered_map<std::string,bool>conditions{};
        public:
            Group(){};
            ~Group(){};
            /**
            *@brief 添加属性
            *@param id：属性id
            *@param condition：true/false
            */
            void add(const std::string &id, bool condition)
            {
                if (conditions.find(id) != conditions.end())
                {
                    throw std::runtime_error("The condition '" + id + "' is added do not readd!");
                }
                conditions[id] = condition;
            }
            /**
            *@brief 重设已有属性
            *@param id：属性id
            *@param condition：true/false
            *@note 找不到抛异常
            */
            void reset(const std::string &id, bool condition)
            {
                if (conditions.find(id) == conditions.end())
                {
                    throw std::runtime_error("The condition '" + id + "' not found.");
                }
                conditions[id] = condition;
            }
            /**
            *@brief 设置所有属性为一个值
            *@param condition：值
            */
            void set_all(bool condition)
            {
                if (conditions.empty())
                {
                    return;
                }
                /**
                *@note 使用前缀自增而不是后缀自增，爱来自B站用户(由衷地，发自内心地感谢你)
                */
                for (auto p = conditions.begin(); p != conditions.end(); ++p)
                {
                    //fixed: use p-> better
                    p->second = condition;
                }
            }
            /**
            *@brief 检查所有属性是否符合条件
            *@param cheak_state：检查方式（与，或，非）
            *@return 返回一个bool结果
            */
            bool check_all(CheckState check_state) const
            {
                if (check_state == CheckState::CS_AND)
                {
                    if (conditions.empty())
                    {
                        return true;
                    }
                    for (auto p = conditions.begin(); p != conditions.end(); ++p)
                    {
                        if (!p->second)
                            return false;
                    }
                    return true;
                }
                else if (check_state == CheckState::CS_OR)
                {
                    if (conditions.empty())
                    {
                        return true;
                    }
                    for (auto p = conditions.begin(); p != conditions.end(); ++p)
                    {
                        if (p->second)
                            return true;
                    }
                    return false;
                }
                else
                {
                    if (conditions.empty())
                    {
                        return false;
                    }
                    for (auto p = conditions.begin(); p != conditions.end(); ++p)
                    {
                        if (p->second)
                            return false;
                    }
                    return true;       
                }
            }
            /**
            *@brief 检查单个属性是否符合条件
            *@param id：属性id
            *@return 返回一个bool结果
            */
            bool check(const std::string &id)
            {
                if (conditions.find(id) == conditions.end())
                {
                    throw std::runtime_error("The condition '" + id + "' not found.");
                }
                return conditions[id];
            }
            /**
            *@brief 获取group大小
            *@return data的size
            */
            size_t size() const noexcept
            {
                return conditions.size();
            }
            /**
            *@brief 删除对应属性
            *@param id：属性id
            */
            void remove(const std::string &id)
            {
                auto it = conditions.find(id);
                if (it != conditions.end())
                {
                    conditions.erase(it);
                }
                else throw std::runtime_error("Cannot find the ID.");
            }
            /**
            *@brief 检查conditions是否为空
            *@return 返回conditions.empty()的bool结果
            */
            bool is_empty() const
            {
                return conditions.empty();
            }
            /**
            *@brief 获取所有id
            *@return 一个vector，装有所有id
            */
            std::vector<std::string> get_id() const
            {
                std::vector<std::string> vec;
                vec.reserve(conditions.size());
                for (auto &k : conditions)
                {
                   vec.push_back(k.first); 
                }
                return vec;
            }
            /**
            *@brief 对所有条件取反
            */
            void flip()
            {
                for (auto &i : conditions)
                {
                    i.second = !i.second;
                }
            }
        };

        using ConditionGroup = Group<bool>;
    }
}

#endif