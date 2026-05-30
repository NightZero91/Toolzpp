#ifndef FLAGERPP_H
#define FLAGERPP_H
/**
 * @file flagerpp.h
 * @date 2026-05-15
 * @author NightZero91
 * @brief 一个状态器，是特殊的conditiongroup，只有一个值为true，适合判断状态
 * @note 欢迎使用者对该文件提出任何建议
 * @warning 多线程请确保加锁
 */
#include "grouppp.h"
#include <stdexcept>
#include <string>

namespace tlz
{
    namespace flager
    {
        class Flager
        {
        private:
            group::ConditionGroup flags;
        public:
            Flager() = delete;
            /**
            *@brief 构造函数，必须传入一个状态
            *@param first_flag：状态id
            *@note 因为必须有一个值为true，所以构造后，first_flag默认为true
            */
            Flager(const std::string &first_flag) { flags.add(first_flag, true); }
            ~Flager() = default;
            /**
            *@brief 添加一个状态
            *@param id：状态id
            */
            void add_flag(const std::string &id)
            {
                if (!flags.is_empty())
                    flags.add(id, false);
                else
                    flags.add(id, true);
            }
            /**
            *@brief 设置某个状态为true
            *@param id：状态id
            */
            void set_flag(const std::string &id)
            {
                flags.set_all(false);
                flags.reset(id, true);
            }
            /**
            *@brief 得到这个flager的状态
            *@note 在单线程情况下，不管逻辑还是理论上这个flager不可能为空，但我还是返回了一个魔法值保命
            *@note 如果你在获取这个flager的状态时得到了"NULL FLAGER"这个魔法值(并且你没有手动添加"NULL FLAGER")，
            那这将是个奇迹，我宁愿相信世界将在24h内毁灭也不相信这个XD
            *@return 返回状态ID
            */
            std::string get_flag()
            {
                for (const auto &i : flags.get_id())
                {
                    if (flags.check(i))
                    {
                        return i;
                    }
                }
                return "NULL FLAGER";
            }
            /**
            *@brief 移除某个状态
            *@param id：状态id
            *@note 移除这个状态时请确保已为false
            *@note 单线程情况下flager不可能为空壳，所以最后一个状态永远无法被删除，如果强制删除，将会抛异常
            */
            void remove_flag(const std::string &id)
            {
                if (flags.check(id)) 
                    throw std::runtime_error("The flag in flags must be false!");
                flags.remove(id);
            }
            /**
            *@brief 获取flag的数量
            *@return 数量
            */
            size_t size() const noexcept
            {
                return flags.size();
            }
        };
    }
}

#endif