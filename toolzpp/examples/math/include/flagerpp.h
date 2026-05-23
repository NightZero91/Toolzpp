#ifndef FLAGERPP_H
#define FLAGERPP_H
//@--flager--toolzpp
//260515
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
            Flager(const std::string &first_flag) { flags.add(first_flag, true); }
            ~Flager() = default;

            void add_flag(const std::string &id)
            {
                if (!flags.is_empty())
                    flags.add(id, false);
                else
                    flags.add(id, true);
            }

            void set_flag(const std::string &id)
            {
                flags.set_all(false);
                flags.reset(id, true);
            }

            std::string get_flag()
            {
                for (auto &i : flags.get_id())
                {
                    if (flags.check(i))
                    {
                        return i;
                    }
                }
                return "NULL FLAG";
            }

            void remove_flag(const std::string &id)
            {
                if (flags.check(id)) 
                    throw std::runtime_error("The flag in flags must be false!");
                flags.remove(id);
            }

        };
    }
}

#endif