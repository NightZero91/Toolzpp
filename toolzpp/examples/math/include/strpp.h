#ifndef STRFORMATPP_H
#define STRFORMATPP_H
//@--strpp--toolzpp
//260515
#include <cstddef>
#include <string>
#include <vector>
#include <stdexcept>
#include <cctype>
#include <array>
#include <type_traits>

namespace tlz
{
    namespace str
    {
        template <class T, size_t N>
        std::string fmt(const std::string& str, const std::array<T, N>& arr)
        {
            std::string fmt_string = str;
            for (size_t i = 0; i < N; i++)
            {
                size_t pos = fmt_string.find("{}");
                if (pos == std::string::npos)
                    break;
                if constexpr(std::is_arithmetic<T>::value && !std::is_same<T, char>::value)
                {
                    fmt_string.replace(pos, 2, std::to_string(arr[i]));
                }
                else if constexpr(std::is_same<T, std::string>::value)
                {
                    fmt_string.replace(pos, 2, arr[i]);
                }
                else if constexpr (std::is_same<T, char>::value)
                {
                    fmt_string.replace(pos, 2, std::string(arr[i]));
                }
                else if constexpr(std::is_same<T, char*>::value || std::is_same<T, const char*>::value) 
                {
                    if (arr[i] == nullptr)
                        throw std::runtime_error("The nullptr in array.");
                    fmt_string.replace(pos, 2, arr[i]);
                }
                else
                    throw std::runtime_error("The arg2 is not support!");
            }
            return fmt_string;
        }

        std::vector<std::string> split(const std::string &str, char split_char)
        {
            std::vector<std::string> result{};
            std::string temp_str{};
            for (const auto& c : str)
            {
                if (c != split_char)
                    temp_str += c;
                else
                {
                    result.push_back(temp_str);
                    temp_str = "";
                }
            }
            result.push_back(temp_str);
            return result;
        }

        std::string upper(const std::string &str)
        {
            std::string tmp_str = str;
            for (size_t i = 0; i < tmp_str.size(); i++)
            {
                if (tmp_str[i] >= 'a' && tmp_str[i] <= 'z')
                {
                    tmp_str[i] = toupper(tmp_str[i]);
                }
            }
            return tmp_str;
        }

        std::string lower(const std::string &str)
        {
            std::string tmp_str = str;
            for (size_t i = 0; i < tmp_str.size(); i++)
            {
                if (tmp_str[i] >= 'A' && tmp_str[i] <= 'Z')
                {
                    tmp_str[i] = tolower(tmp_str[i]);
                }
            }
            return tmp_str;
        }

        std::string upper(const std::string &str, const std::pair<size_t, size_t> &range)
        {
            std::string tmp_str = str;
            if (range.second >= tmp_str.size() || range.first < 0 || range.first > range.second)
            {
                throw std::runtime_error("The arg2 is too big");
            }
            for (auto i = range.first; i < range.second; i++)
            {
                if (tmp_str[i] >= 'a' && tmp_str[i] <= 'z')
                {
                    tmp_str[i] = toupper(tmp_str[i]);
                }
            }
            return tmp_str;
        }

        std::string lower(const std::string &str, const std::pair<size_t, size_t> &range)
        {
            std::string tmp_str = str;
            if (range.second >= tmp_str.size() || range.first < 0 || range.first > range.second)
            {
                throw std::runtime_error("The arg2 is too big");
            }
            for (size_t i = range.first; i < range.second; i++)
            {
                if (tmp_str[i] >= 'A' && tmp_str[i] <= 'Z')
                {
                    tmp_str[i] = tolower(tmp_str[i]);
                }
            }
            return tmp_str;
        }

        bool contains(const std::string &str, const std::string &dst)
        {
            if (str.empty())
                return false;
            return (str.find(dst) != std::string::npos);
        }

        std::string join(const std::vector<std::string> &vec, const char &c)
        {
            std::string tmp_str = "";
            for (auto i : vec)
            {
                tmp_str += (i + c);
            }
            if (!tmp_str.empty())
                tmp_str.pop_back();
            return tmp_str;
        }

        std::string replace(const std::string &str, const char &fid, const char &dst)
        {
            auto tmp_str = str;
            for (auto &c : tmp_str)
            {
                if (c == fid)
                    c = dst;
            }
            return tmp_str;
        }

        std::string strip(const std::string &str)
        {
            std::string tmp_str = str;
            for (auto p = tmp_str.begin(); p != tmp_str.end();)
            {
                if (*p == ' ')
                {
                    p = tmp_str.erase(p);
                    continue;
                }
                p++;
            }
            return tmp_str;
        }

        bool is_digit(const std::string &str)
        {
            if (str.empty()) return false;
            for (auto &c : str)
            {
                if (!(c >= '0' && c <= '9'))
                    return false;
            }
            return true;
        }

        bool is_number(const std::string &str)
        {
            if (str.empty()) return false;
            bool has_dot = false;
            for (size_t i = 0; i < str.size(); i++)
            {
                if (i == 0 && (str[i] == '-' || str[i] == '+')) continue;
                if (!(str[i] >= '0' && str[i] <= '9'))
                {
                    if (!has_dot && i !=0)
                    {
                        has_dot = true;
                        continue;
                    }
                    return false;
                }
            }
            return true;
        }

        std::vector<char> to_chars(const std::string& str)
        {
            std::vector<char>res{};
            res.reserve(str.size());
            for (const auto &c : str)
            {
                res.push_back(c);
            }
            return res;
        }

        std::vector<int> to_ascii_codes(const std::string& str)
        {
            std::vector<int>res{};
            res.reserve(str.size());
            for (const auto &c : str)
            {
                res.push_back(static_cast<int>(c));
            }
            return res;
        }

        std::string reverse(const std::string& source)
        {
            if (source.empty()) return std::string("");
            auto str = source;
            for (size_t i = 0; i < str.size() / 2; i++)
            {
                auto tmp = str[i];
                str[i] = str[str.size() - i - 1];
                str[str.size() - i - 1] = tmp;
            }
            return str;
        }
    }
}

#endif