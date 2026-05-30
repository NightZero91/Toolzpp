#ifndef TREEPP_H
#define TREEPP_H
/**
 * @file treepp.h
 * @date 2026-05-15
 * @author NightZero91
 * @brief 含有简单二叉树和链表的文件
 * @note 欢迎使用者对该文件提出任何建议
 */
#include <cstddef>
#include <utility>
#include <stdexcept>
#include <memory>

namespace tlz
{
    namespace tree
    {
        /**
        *@brief 一个RAII的二叉树
        *@note 二叉树只有一个跟，却有无数的分支，就像宇宙万物的答案只有一个
        */
        template<class Type>
        class DoubleTree
        {
        private:
            Type value;
            std::pair<std::unique_ptr<DoubleTree<Type>>, std::unique_ptr<DoubleTree<Type>>> next;
        public:
            DoubleTree() = delete;
            /**
            *@brief 构造一个二叉树
            *@param _value 二叉树根值
            */
            DoubleTree(const Type &_value) : value(_value), next({ nullptr, nullptr }) {}

            DoubleTree(const DoubleTree&) = delete;

            DoubleTree& operator=(const DoubleTree&) = delete;

            DoubleTree(DoubleTree&&) = delete;

            DoubleTree& operator=(DoubleTree&&) = delete;

            ~DoubleTree() = default;

            /**
            * @brief 检查是否同时拥有左右子节点
            * @return true 如果左右子节点都存在，false 否则
            * @note 要求两个子节点都存在才算有"下一个"
            */
            bool has_next() const noexcept
            {
                return (next.first && next.second);
            }

            /**
            * @brief 检查是否存在右子节点
            * @return true 如果右子节点存在，false 否则
            */
            bool has_right() const noexcept
            {
                return (next.second);
            }

            /**
            * @brief 检查是否存在左子节点
            * @return true 如果左子节点存在，false 否则
            */
            bool has_left() const noexcept
            {
                return (next.first);
            }

            /**
            * @brief 同时创建左右子节点
            * @param pair 包含左右子节点值 (first=左子节点值, second=右子节点值)
            * @note 只能创建一次，创建后不可重复调用，但我希望和她相遇不止一次.
            */
            void create_bif(const std::pair<Type, Type> &pair)
            {
                if (has_next())
                {
                    throw std::runtime_error("Already has next nodes!");
                }
                next.first = std::make_unique<DoubleTree<Type>>(pair.first);
                next.second = std::make_unique<DoubleTree<Type>>(pair.second);
            }

            /**
            * @brief 获取子节点对的引用
            * @return std::pair<std::unique_ptr<DoubleTree<Type>>, std::unique_ptr<DoubleTree<Type>>>& 子节点对的引用
            */
            std::pair<std::unique_ptr<DoubleTree<Type>>, 
            std::unique_ptr<DoubleTree<Type>>>& get_next()
            {
                if (has_next())
                    return next;
                else
                    throw std::runtime_error("The object does not have next!");
            }

            /**
            * @brief 获取节点存储的值
            * @return Type 值的拷贝
            */
            Type get_value() const noexcept
            {
                return value;
            }

            /**
            * @brief 设置节点存储的值
            * @param _value 新值
            */
            void set_value(const Type &_value)
            {
                value = _value;
            }

            /**
            * @brief 重置子节点
            * @param pair 新的左右子节点值
            * @note 会先销毁旧的子节点，再创建新的
            */
            void reset_next(const std::pair<Type, Type> &pair)
            {
                if (has_next())
                {
                    next.first.reset();
                    next.second.reset();
                    next.first = std::make_unique<DoubleTree<Type>>(pair.first);
                    next.second = std::make_unique<DoubleTree<Type>>(pair.second);
                }
                else
                    throw std::runtime_error("The object does not have next!");
            }

            /**
            * @brief 移除整个子树
            * @note 会递归销毁所有子节点，不删除根节点
            */
            void remove_subtree()
            {
                if (has_next())
                {
                    next.first.reset();
                    next.second.reset();
                }
            }
            };

        /**
        * @brief 单链表节点类
        * @tparam Type 节点存储的数据类型
        * @note 使用 std::unique_ptr 管理内存，无需手动 delete
        */
        template<class Type>
        class SingleTree 
        {
        private:
            Type value;
            std::unique_ptr<SingleTree<Type>> next;

            /**
            * @brief 检查是否存在下一个节点
            * @return bool结果
            */
            bool has_next() const noexcept 
            {
                return next != nullptr;
            }

        public:
            SingleTree() = delete;
                
            /**
            * @brief 构造一个单链表节点
            * @param _value 节点存储的值
            */
            explicit SingleTree(const Type& _value) 
                : value(_value), next(nullptr) {}

            SingleTree(const SingleTree&) = delete;
            SingleTree(SingleTree&&) = delete;
            SingleTree& operator=(const SingleTree&) = delete;
            SingleTree& operator=(SingleTree&&) = delete;

            ~SingleTree() = default;

            /**
            * @brief 创建下一个节点
            * @param _value 下一个节点存储的值
            */
            void create_next(const Type& _value) 
            {
                if (has_next()) 
                {
                    throw std::runtime_error("Already has next node!");
                }
                next = std::make_unique<SingleTree<Type>>(_value);
            }

            /**
            * @brief 获取下一个节点的指针
            * @return SingleTree<Type>* 下一个节点的指针，可能为 nullptr
            */
            SingleTree<Type>* get_next() noexcept 
            {
                return next.get();
            }
                
            /**
            * @brief 获取下一个节点的指针
            * @return SingleTree<Type>* const 下一个节点的指针
            */
            SingleTree<Type>* const get_next() const noexcept 
            {
                return next.get();
            }

            /**
            * @brief 弹出下一个节点
            * @note 删除下一个节点，并将当前节点连接到下下个节点
            * @note 相当于跳过下一个节点
            */
            void pop_next() noexcept 
            {
                if (next) 
                {
                    next = std::move(next->next);
                }
            }

            /**
            * @brief 获取节点存储的值
            */
            const Type& get_value() const noexcept 
            {
                return value;
            }
                
                /**
                * @brief 获取节点存储的值（可修改版本）
                * @return Type& 值的引用
                */
                Type& get_value() noexcept 
                {
                    return value;
                }

                /**
                * @brief 设置节点存储的值
                * @param _value 新值
                */
                void set_value(const Type& _value) noexcept 
                {
                    value = _value;
                }

                /**
                * @brief 重置下一个节点的值
                * @param new_value 新的下一个节点的值
                * @note 会保留后续链表的连接
                */
                void reset_next(const Type& new_value) 
                {
                    if (!has_next()) 
                    {
                        throw std::runtime_error("No next node to reset!");
                    }
                    auto new_next = std::make_unique<SingleTree<Type>>(new_value);
                    new_next->next = std::move(next->next);
                    next = std::move(new_next);
                }

                /**
                * @brief 清空后续所有节点
                * @note 删除当前节点之后的所有节点
                */
                void clear() noexcept 
                {
                    next.reset();
                }

                /**
                * @brief 通过索引访问节点
                * @param offset 偏移量
                * @return SingleTree<Type>* 目标节点的裸指针
                */
                SingleTree<Type>* operator[](size_t offset) 
                {
                    SingleTree<Type>* current = this;
                    for (size_t i = 0; i < offset; ++i) 
                    {
                        if (!current->next) 
                        {
                            throw std::out_of_range("Index out of range");
                        }
                        current = current->next.get();
                    }
                    return current;
                }
                
                /**
                * @brief 通过索引访问节点（const 版本）
                * @param offset 偏移量
                * @return const SingleTree<Type>* 目标节点的常量指针
                */
                const SingleTree<Type>* operator[](size_t offset) const 
                {
                    const SingleTree<Type>* current = this;
                    for (size_t i = 0; i < offset; ++i) 
                    {
                        if (!current->next) 
                        {
                            throw std::out_of_range("Index out of range");
                        }
                        current = current->next.get();
                    }
                    return current;
                }

                /**
                * @brief 获取链表的总节点数
                * @return size_t 从当前节点开始的节点总数
                */
                size_t size() const noexcept 
                {
                    size_t count = 1;
                    const SingleTree* current = next.get();
                    while (current) 
                    {
                        ++count;
                        current = current->next.get();
                    }
                    return count;
                }

                /**
                * @brief 检查是否为叶子节点（没有下一个节点）
                * @return bool结果
                */
                bool is_leaf() const noexcept 
                {
                    return !has_next();
                }
            };
        }
}
#endif