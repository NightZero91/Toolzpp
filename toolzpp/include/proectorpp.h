#ifndef PROECTORPP_H
#define PROECTORPP_H
//@--proector--toolzpp
//260515

namespace tlz
{
    namespace proector
    {
        template<class Type>
        class WriteProector
        {
        private:
            Type &value;
            bool is_lock;
        public:
            WriteProector() = delete;

            WriteProector(Type &_value) : value(_value), is_lock(false) {}

            WriteProector(const WriteProector &) = delete;

            WriteProector(WriteProector&&) = delete;

            WriteProector& operator=(const WriteProector&) = delete;

            WriteProector& operator=(WriteProector&&) = delete;

            ~WriteProector() = default;

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