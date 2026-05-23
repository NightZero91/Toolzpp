#ifndef GROUPPP_H
#define GROUPPP_H
//@--grouppp--toolzpp
//260515
#include <string>
#include <vector>
#include <unordered_map>
#include <stdexcept>

namespace tlz
{
    enum CheckState
    {
        CS_AND,
        CS_OR,
        CS_NOT
    };

    namespace group
    {
        //basic group class
        template<class V>
        class Group
        {
        private:
            std::unordered_map<std::string, V> data;
        public:
            Group(){};
            ~Group(){};
            //添加组元素
            void add(const std::string &id, V value)
            {
                if (data.find(id) != data.end())
                {
                    throw std::runtime_error("The value '" + id + "' is added do not readd!");
                }
                data[id] = value;
            }
            //重设对应的组元素
            void reset(const std::string &id, V value)
            {
                if (data.find(id) == data.end())
                {
                    throw std::runtime_error("The value '" + id + "' not found.");
                }
                data[id] = value;
            }
            //大小
            size_t size() const
            {
                return data.size();
            }
            //重设所有的组元素
            void set_all(V value)
            {
                if (data.empty())
                {
                    return;
                }
                for (auto p = data.begin(); p != data.end(); p++)
                {
                    (*p).second = value;
                }
            }
            //获取对应的组元素
            V get(const std::string &id) const
            {
                if (data.find(id) == data.end())
                {
                    throw std::runtime_error("The value '" + id + "' not found.");
                }
                return data[id];
            }
            //判断是否为空
            bool is_empty() const
            {
                return data.empty();
            }
            //获取id
            std::vector<std::string> get_id() const
            {
                std::vector<std::string> vec;
                vec.reserve(data.size());
                for (auto &k : data)
                {
                   vec.push_back(k.first); 
                }
                return std::move(vec);
            }
        };
        //特化类
        template<>
        class Group<bool>
        {
        private:
            std::unordered_map<std::string,bool>conditions{};
        public:
            Group(){};
            ~Group(){};
            //添加组元素
            void add(const std::string &id, bool condition)
            {
                if (conditions.find(id) != conditions.end())
                {
                    throw std::runtime_error("The condition '" + id + "' is added do not readd!");
                }
                conditions[id] = condition;
            }
            //重设对应的组元素
            void reset(const std::string &id, bool condition)
            {
                if (conditions.find(id) == conditions.end())
                {
                    throw std::runtime_error("The condition '" + id + "' not found.");
                }
                conditions[id] = condition;
            }
            //重设所有的组元素
            void set_all(bool condition)
            {
                if (conditions.empty())
                {
                    return;
                }
                for (auto p = conditions.begin(); p != conditions.end(); p++)
                {
                    (*p).second = condition;
                }
            }
            //检查所有组元素是否符合要求
            bool check_all(CheckState check_state) const
            {
                if (check_state == CheckState::CS_AND)
                {
                    if (conditions.empty())
                    {
                        return true;
                    }
                    for (auto p = conditions.begin(); p != conditions.end(); p++)
                    {
                        if (!(*p).second)
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
                    for (auto p = conditions.begin(); p != conditions.end(); p++)
                    {
                        if ((*p).second)
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
                    for (auto p = conditions.begin(); p != conditions.end(); p++)
                    {
                        if ((*p).second)
                            return false;
                    }
                    return true;       
                }
            }
            //检查对应组元素是否符合要求
            bool check(const std::string &id)
            {
                if (conditions.find(id) == conditions.end())
                {
                    throw std::runtime_error("The condition '" + id + "' not found.");
                }
                return conditions[id];
            }
            //获取大小
            size_t size() const 
            {
                return conditions.size();
            }
            //移除对应组元素
            void remove(const std::string &id)
            {
                auto it = conditions.find(id);
                if (it != conditions.end())
                {
                    conditions.erase(it);
                }
            }
            //判断是否为空
            bool is_empty() const
            {
                return conditions.empty();
            }

            //获取id
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

            void flip()
            {
                for (auto &i : conditions)
                {
                    i.second = !i.second;
                }
            }
        };
        //设置别名
        using ConditionGroup = Group<bool>;
    }
}

#endif