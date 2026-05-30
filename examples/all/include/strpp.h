#ifndef STRPP_H
#define STRPP_H
/**
 * @file strpp.h
 * @date 2026-05-01
 * @author NightZero91
 * @brief 一个多函数的str文件，提供了许多标准库都没有的string处理函数
  * @note 欢迎使用者对该文件提出任何建议
---------------------------------------------------
  _____                   _                         
 |_   _|   ___     ___   | |  ____  _ __    _ __    
   | |    / _ \   / _ \  | | |_  / | '_ \  | '_ \   
   | |   | (_) | | (_) | | |  / /  | |_) | | |_) |  
   |_|    \___/   \___/  |_| /___| | .__/  | .__/ 
                                   |_|     |_|    
---------------------------------------------------
 */
#include <cstddef>
#include <iterator>
#include <string>
#include <vector>
#include <stdexcept>
#include <cctype>
#include <array>
#include <type_traits>
#include <algorithm>

namespace tlz
{
    namespace str
    {
        /**
        *@brief 根据字符将字符串拆分为单词
        *@param str：要格式化的字符串
        *@param split：根据这个字符拆分为单词
        *@return 返回一个vector<std::string>
        *@note - - - - - - 请沿虚线剪开这个字符串 - - - - - - -
        */
        inline std::vector<std::string> split(const std::string &str, char split_char)
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

        /**
        *@brief 传入数组实现字符串格式化
        *@tparam N：数组大小
        *@tparam T：数组类型
        *@param str：要格式化的字符串
        *@param arr：数组数据
        */
        template <class T, size_t N>
        std::string fmt(const std::string& str, const std::array<T, N>& arr)
        {
            if (str.empty()) return "";
            std::string fmt_string = str;
            size_t pos = 0;
            for (size_t i = 0; i < N; i++)
            {
                pos = fmt_string.find("{}", pos);
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
        /**
        *@brief 将字符串全大写
        *@param str：要大写的字符串
        *@return 新字符串
        *@note WHY C++ NOT HAS toupper(str)???LOOKING MY EYS AND A-N-S-W-E-R THE QUESTION!!!(开玩笑的)
        */
        inline std::string upper(const std::string &str)
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
        /**
        *@brief 将字符串全小写
        *@param str：要小写的字符串
        *@return 新字符串
        *@note same question like upper:)
        */
        inline std::string lower(const std::string &str)
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
        /**
        *@brief 将指定范围的字符串全大写
        *@param str：要大写的字符串
        *@param range：大写的范围
        *@return 新字符串
        */
        inline std::string upper(const std::string &str, const std::pair<size_t, size_t> &range)
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
        /**
        *@brief 将指定范围的字符串全小写
        *@param str：要小写的字符串
        *@param range：小写的范围
        *@return 新字符串
        */
        inline std::string lower(const std::string &str, const std::pair<size_t, size_t> &range)
        {
            std::string tmp_str = str;
            if (range.second >= tmp_str.size() || range.first < 0 || range.first > range.second)
            {
                throw std::runtime_error("The arg2 is too big");
            }
            for (size_t i = range.first; i < range.second; ++i)
            {
                if (tmp_str[i] >= 'A' && tmp_str[i] <= 'Z')
                {
                    tmp_str[i] = tolower(tmp_str[i]);
                }
            }
            return tmp_str;
        }
        /**
        *@brief 寻找一个字符串是否在另一个字符串中存在
        *@param str：被寻找的串
        *@param dst：子串
        *@return bool结果
        *@note 人的一生像contains，寻找着它的意义.
        */
        inline bool contains(const std::string &str, const std::string &dst)
        {
            if (str.empty())
                return false;
            return (str.find(dst) != std::string::npos);
        }
        /**
        *@brief 将一个字符加入到vector的不同元素的间隙里，并遍历vector，将他们拼接
        *@param vec：要遍历的vector
        *@param c：链接字符
        *@return 新字符串
        *@note “破碎”字符串是冰冷的机器拼的，而我对她的回忆是炽热的我哭着一点一点拼好的.
        */
        inline std::string join(const std::vector<std::string> &vec, const char &c)
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
        /**
        *@brief 将字符串里的指定字符替换为其他字符
        *@param str：被操作的字符串
        *@param fid：被替换的字符
        *@param dst：替换后的字符
        *@return 字符可以被换掉，而我对她的心却不能.
        */
        inline std::string replace(const std::string &str, const char &fid, const char &dst)
        {
            auto tmp_str = str;
            for (auto &c : tmp_str)
            {
                if (c == fid)
                    c = dst;
            }
            return tmp_str;
        }
        /**
        *@brief 去掉字符串首尾的空格
        *@param str：被操作的字符串
        *@return 新字符串
        */
        inline std::string trim(const std::string &str)
        {
            std::string tmp_str = str;
            for (auto p = tmp_str.begin(); p != tmp_str.end();)
            {
                if (*p == ' ')
                {
                    p = tmp_str.erase(p);
                    continue;
                }
                ++p;
            }
            return tmp_str;
        }
        /**
        *@brief 检测字符串是不是纯数字
        *@param str：被检测的字符串
        *@return bool结果
        *@note 只有像42 67 0这样的数字才能通过
        */
        inline bool is_digit(const std::string &str)
        {
            if (str.empty()) return false;
            for (auto &c : str)
            {
                if (!(c >= '0' && c <= '9'))
                    return false;
            }
            return true;
        }
        /**
        *@brief 检测字符串是不是实数
        *@param str：被检测的字符串
        *@return bool结果
        *@note 所有实数均可通过
        */
        inline bool is_number(const std::string &str)
        {
            if (str.empty()) return false;
            bool has_dot = false;
            for (size_t i = 0; i < str.size(); i++)
            {
                if (i == 0 && (str[i] == '-' || str[i] == '+')) continue;
                if (str[str.size() - 1] == '.') return false;
                if (!(str[i] >= '0' && str[i] <= '9'))
                {
                    if (!has_dot && i != 0)
                    {
                        has_dot = true;
                        continue;
                    }
                    return false;
                }
            }
            return true;
        }
        /**
        *@brief 将字符串拆成字符vector
        *@param str：被操作的字符串
        *@return vector<char>
        *@note 万物皆可vector
        */
        inline std::vector<char> to_chars(const std::string& str)
        {
            std::vector<char>res{};
            res.reserve(str.size());
            for (const auto &c : str)
            {
                res.push_back(c);
            }
            return res;
        }
        /**
        *@brief 将字符串转为ascii向量
        *@param str：被操作的字符串
        *@return vector<int>
        *@note 这是一个冷门的函数
        */
        //I GUESS ONLY A FEW PEOPLE use it:(
        inline std::vector<int> to_ascii_codes(const std::string& str)
        {
            std::vector<int>res{};
            res.reserve(str.size());
            for (const auto &c : str)
            {
                res.push_back(static_cast<int>(c));
            }
            return res;
        }
        /**
        *@brief 反转字符串
        *@param str：被操作的字符串
        *@return 新字符串
        *@note 我曾将他们的地盘给翻了过来
        */
        inline std::string reverse(const std::string& source)
        {
            if (source.empty()) return std::string("");
            auto str = source;
            // for (size_t i = 0; i < str.size() / 2; ++i)
            // {
            //     auto tmp = str[i];
            //     str[i] = str[str.size() - i - 1];
            //     str[str.size() - i - 1] = tmp;
            // }
            std::reverse(str.begin(), str.end());
            return str;
        }
        /**
        *@brief 过滤掉字符串不含有某字串的[单词]
        *@param str：被操作的字符串
        *@param can_find：要含有的单词
        *@return vector<std::string>
        *@note *被空格分隔的字串定义为[单词]
        */
        inline std::vector<std::string> word_filter(const std::string &str, const std::string &can_find, size_t reserve_size = 0)
        {
            if (str.empty()) return std::vector<std::string>{};
            std::vector<std::string>result;
            if (reserve_size > 0)
            {
                result.reserve(reserve_size);
            }
            auto s_result = split(str, ' ');
            std::copy_if(s_result.begin(), s_result.end(), std::back_inserter(result), 
        [&can_find](const std::string &str){ return str.find(can_find) != std::string::npos;});
            return result;
        }
        /**
        *@brief 统计一个[单词]出现的频率
        *@param str：被操作的字符串
        *@param word：单词
        *@return size_t频率
        *@note *被空格分隔的字串定义为[单词]
        */
        inline size_t word_counter(const std::string &str, const std::string &word)
        {
            if (str.empty()) return 0;
            size_t sum = 0;
            auto vec = split(str, ' ');
            for (const auto i : vec)
            {
                if (i == word) ++sum;
            }
            return sum;
        }
        /**
        *@brief 检测一个字符串开头是否携带指定字串
        *@param str：被操作的字符串
        *@param word：字串
        *@return bool结果
        */
        inline bool start_with(const std::string &str, const std::string &word)
        {
            return str.find(word) == 0;
        }
        /**
        *@brief 检测一个字符串结尾是否携带指定字串
        *@param str：被操作的字符串
        *@param word：字串
        *@return bool结果
        */
        inline bool end_with(const std::string &str, const std::string &word)
        {
            if (str.empty()) return false;
            if (str.size() < word.size()) return false;
            return str.find(word) == str.size() - word.size();
        }
    }
}

#endif