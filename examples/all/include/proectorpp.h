#ifndef PROECTORPP_H
#define PROECTORPP_H
//@--proector--toolzpp
//260515

//A basic lock
//DO NOT use it when you're using thread
namespace tlz
{
    namespace protector
    {
        //if lock you cannot change this obj,
        //BUT you can change the source value outside
        template<class Type>
        class WriteProtector
        {
        private:
            //have a &value
            Type &value;
            bool is_lock;
        public:
            //NOT copy or move
            WriteProtector() = delete;

            WriteProtector(Type &_value) : value(_value), is_lock(false) {}

            WriteProtector(const WriteProtector &) = delete;

            WriteProtector(WriteProtector&&) = delete;

            WriteProtector& operator=(const WriteProtector&) = delete;

            WriteProtector& operator=(WriteProtector&&) = delete;

            ~WriteProtector() = default;

            Type value_copy() const noexcept
            {
                return value;
            }

            bool set(const Type& _value)
            {
                if (!is_lock)
                {
                    value = _value;
                    return true;
                }
                return false;
            }

            void lock() noexcept { is_lock = true; }
            void unlock() noexcept { is_lock = false; }

            bool get_lock() const noexcept { return is_lock; }
        };
    }
}

#endif