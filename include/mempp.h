#ifndef MEMPP_H
#define MEMPP_H
/**
 * @file mempp.h
 * @date 2026-05-29
 * @author NightZero91
 * @brief 一个专门管理内存的文件，提供了内存处理函数
 * @note 欢迎使用者对该文件提出任何建议
 * @warning
 * 一些函数已经不适合现代C++，但我还是将他们保留了下来，专门给予老式写法调用，请记得及时释放
 * 你的内存哦~喵~
 */

#include <cstddef>
#include <optional>
#include <stdexcept>
#include <utility>
#include <vector>
namespace tlz 
{
    namespace mem 
    {
        /**
        *@brief 安全地解引用，在某些情况下能避免空指针
        *@param ptr:原指针
        *@tparam T:指针类型
        *@note 本质是将指针解引用转为opt,如同std::move其实只做了转换
        *@code if (safe_deref(aptr)){...})
        */
        template<class T>
        std::optional<T> safe_deref(const T* const ptr)
        {
            if (ptr == nullptr) return std::nullopt;
            else return std::optional<T>(*ptr);
        }
        
        /**
        *@brief 释放指向同一区域的指针
        *@param ptrs:指向同一区域的指针向量
        *@tparam T:指针类型
        *@warning 请确保所有指针未被释放，且此函数【默认假设】所有指针都指向同一区域！！！
        *@warning 请确保所有指针未被释放，且此函数【默认假设】所有指针都指向同一区域！！！
        *@warning 请确保所有指针未被释放，且此函数【默认假设】所有指针都指向同一区域！！！
        *@warning 这有点像C写法，如果你没有这样的需求，请不要使用它
        */
        template<class T>
        void delete_shared_ptr_array(std::vector<T*> &ptrs)
        {
            if (ptrs.empty()) return;
            
            T* shared_ptr = ptrs[0];
            
            for (size_t i = 1; i < ptrs.size(); ++i) 
            {
                ptrs[i] = nullptr;
            }
            
            delete shared_ptr;
            
            ptrs.clear();  
        }
        /**
        *@brief 简单的unique_ptr，但是带检查
        *@note 在某些情况下防止空指针
        *@tparam T:指针的类型
        *@code 举个超级简单的栗子:

        cpp:
        #include <mempp.h>
        #include <iostream>

        class Player
        {
        public:
            void move()
            {
                std::cout << "move\n";
            }
        };

        int main()
        {
            //create
            auto p = tlz::mem::UniPtr<Player>();
            p->move();
            //auto free
        }

        */
        template<class T>
        class UniPtr
        {
        private:
            //指针数据
            T* data = nullptr;  
        public:
            /**
            *@brief 构造一个对象，从一个裸指针
            *@param ptr:裸指针
            *@note 常用来传nullptr
            */
            explicit UniPtr(T* ptr) : data(ptr){};
            /**
            * @brief 构造一个对象，从一堆构造参数
            * @param args:指向对象的构造参数
            * @tparam Args:参数的类型
            */
            template<class ...Args>
            explicit UniPtr(Args&& ...args) : data(new T(std::forward<Args>(args)...)) {}
            
            //移动及拷贝构造区
            //------------------------------------------------------------
            UniPtr(const UniPtr&) = delete;

            UniPtr& operator=(const UniPtr&) = delete;

            UniPtr(UniPtr&& other)
            {
                this->data = other.data;
                other.data = nullptr;
            }

            UniPtr& operator=(UniPtr&& other)
            {
                if (&other == this) return *this;
                if (this->data) delete this->data;
                this->data = other.data;
                other.data = nullptr;

                return *this;
            }
            //------------------------------------------------------------

            ~UniPtr()
            {
                if (this->data) delete this->data;
            }

            /**
            *@brief 释放指针
            */
            void free()
            {
                if (this->data) delete this->data;
                this->data = nullptr;
            }

            /**
            *@brief 访问本对象里的data
            *@note 与unique_ptr不同，会对nullptr的情况抛异常
            */
            T* const operator->()
            {
                if (data)
                    return data;
                else
                    throw std::runtime_error("Cannot nullptr->.");
            }

            /**
            *@brief 解引用本对象里的data
            *@note 与unique_ptr不同，会对nullptr的情况抛异常
            */
            T& operator*()
            {
                if (data)
                    return *data;
                else
                    throw std::runtime_error("Cannot *nullptr.");
            }

            /**
            *@brief 访问本const对象里的data
            *@note 与unique_ptr不同，会对nullptr的情况抛异常
            */
            const T* const operator->() const
            {
                if (data)
                    return data;
                else
                    throw std::runtime_error("Cannot nullptr->.");
            }

            /**
            *@brief 解引用本const对象里的data
            *@note 与unique_ptr不同，会对nullptr的情况抛异常
            */
            const T& operator*() const
            {
                if (data)
                    return *data;
                else
                    throw std::runtime_error("Cannot *nullptr.");
            }

            /**
            *@brief 判断指针是否为空的重载
            */
            explicit operator bool() const noexcept
            {
                return data != nullptr;
            }

            /**
            *@brief 安全获取指针
            *@note 对于nullptr会抛异常
            */
            T* safe_get()
            {
                if (!data) throw std::runtime_error("Cannot get a nullptr.");
                return data;
            }

            /**
            *@brief 获取指针
            */
            T* get() { return data; }
        };
    }
}

#endif