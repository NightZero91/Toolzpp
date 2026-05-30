#ifndef PROTECTORPP_H
#define PROTECTORPP_H
/**
 * @file protectorpp.h
 * @date 2026-05-15
 * @author NightZero91
 * @brief 一个简易的保护器
 * @note 欢迎使用者对该文件提出任何建议
 * @warning 此保护器线程不安全！！！在未加锁情况下不建议使用
 * @note 只有唯一的线程，就像是你，我的唯一.
 */
namespace tlz
{
    namespace protector
    {
        template<class Type>
        /**
        *@brief 持有值的引用，对值进行写保护
        */
        class WriteProtector
        {
        private:
            Type &value;
            bool is_lock;
        public:
            //静止拷贝或移动
            WriteProtector() = delete;

            WriteProtector(Type &_value) : value(_value), is_lock(false) {}

            WriteProtector(const WriteProtector &) = delete;

            WriteProtector(WriteProtector&&) = delete;

            WriteProtector& operator=(const WriteProtector&) = delete;

            WriteProtector& operator=(WriteProtector&&) = delete;

            ~WriteProtector() = default;
            /**
            *@brief 获取该保护器的值
            *@return 获取拷贝形式
            */
            Type value_copy() const noexcept
            {
                return value;
            }
            /**
            *@brief 设置该保护器的值
            *@param _value：要设置的值
            *@return 返回布尔值表示设置是否成功
            */
            bool set(const Type& _value)
            {
                if (!is_lock)
                {
                    value = _value;
                    return true;
                }
                return false;
            }
            /**
            *@brief 将保护器进行锁定
            */
            void lock() noexcept { is_lock = true; }
            /**
            *@brief 将保护器进行解锁
            */
            void unlock() noexcept { is_lock = false; }
            /**
            *@brief 获取该保护器的状态
            */
            bool get_lock() const noexcept { return is_lock; }
        };
    }
}

#endif