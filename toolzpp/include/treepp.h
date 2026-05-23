#ifndef TREEPP_H
#define TREEPP_H
//--outputpp--toolzpp
//260515
#include <cstddef>
#include <utility>
#include <stdexcept>
#include <memory>

namespace tlz
{
    namespace tree
    {
        //二叉树类
        template<class Type>
        class DoubleTree
        {
        private:
            Type value;
            std::pair<std::unique_ptr<DoubleTree<Type>>, std::unique_ptr<DoubleTree<Type>>> next;
        public:
            DoubleTree() = delete;

            DoubleTree(const Type &_value) : value(_value), next({ nullptr, nullptr }) {}

            DoubleTree(const DoubleTree&) = delete;

            DoubleTree& operator=(const DoubleTree&) = delete;

            DoubleTree(DoubleTree&&) = delete;

            DoubleTree& operator=(DoubleTree&&) = delete;

            ~DoubleTree() = default;

            bool has_next() const noexcept
            {
                return (next.first && next.second);
            }

            bool has_right() const noexcept
            {
                return (next.second);
            }

            bool has_left() const noexcept
            {
                return (next.first);
            }

            void create_bif(const std::pair<Type, Type> &pair)
            {
                if (has_next())
                {
                    throw std::runtime_error("Already has next nodes!");
                }
                next.first = std::make_unique<DoubleTree<Type>>(pair.first);
                next.second = std::make_unique<DoubleTree<Type>>(pair.second);
            }

            std::pair<std::unique_ptr<DoubleTree<Type>>, 
            std::unique_ptr<DoubleTree<Type>>>& get_next()
            {
                if (has_next())
                    return next;
                else
                    throw std::runtime_error("The object does not have next!");
            }

            Type get_value() const noexcept
            {
                return value;
            }

            void set_value(const Type &_value)
            {
                value = _value;
            }

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

            void remove_subtree()
            {
                if (has_next())
                {
                    next.first.reset();
                    next.second.reset();
                }
            }
        };
        template<class Type>
        class SingleTree 
        {
        private:
            Type value;
            std::unique_ptr<SingleTree<Type>> next;

            bool has_next() const noexcept 
            {
                return next != nullptr;
            }

        public:
            SingleTree() = delete;
            
            explicit SingleTree(const Type& _value) 
                : value(_value), next(nullptr) {}

            SingleTree(const SingleTree&) = delete;
            SingleTree(SingleTree&&) = delete;
            SingleTree& operator=(const SingleTree&) = delete;
            SingleTree& operator=(SingleTree&&) = delete;

            ~SingleTree() = default;

            void create_next(const Type& _value) 
            {
                if (has_next()) 
                {
                    throw std::runtime_error("Already has next node!");
                }
                next = std::make_unique<SingleTree<Type>>(_value);
            }

            SingleTree<Type>* get_next() noexcept 
            {
                return next.get();
            }
            
            SingleTree<Type>* const get_next() const noexcept 
            {
                return next.get();
            }

            // pop: 删除下一个节点（不提拔）
            void pop_next() noexcept 
            {
                if (next) 
                {
                    next = std::move(next->next);
                }
            }

            const Type& get_value() const noexcept 
            {
                return value;
            }
            
            Type& get_value() noexcept 
            {
                return value;
            }

            void set_value(const Type& _value) noexcept 
            {
                value = _value;
            }

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

            void clear() noexcept 
            {
                next.reset();
            }

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

            bool is_leaf() const noexcept 
            {
                return !has_next();
            }
            
            bool is_root() const noexcept 
            {
                return false;
            }
        };
    }
}

#endif