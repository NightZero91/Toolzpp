#ifndef FILEPP_H
#define FILEPP_H
/**
 * @file filepp.h
 * @date 2026-06-05
 * @author NightZero91
 * @brief 一个极致简化文件操作的头文件
 * @note 欢迎使用者对该文件提出任何建议
 * @note 简单的读写只要一行read_all_text
 * @note 想要拿捏她的内心可比调用这个API难多了:(
 */

 //这是一段写给作者的注释：
 //fstream请指定模式打开
 //读写记得查询bad/失败
 //写完记得flush

#include <fstream>
#include <stdexcept>
#include <string>
#include <sys/stat.h>
#include <utility>

namespace tlz 
{
    namespace file 
    {
        /**
        * @brief 文件基类，使用file
        * @param file：文件
        * @param fpath：文件路径
        * @note 文件接口类
        */
        class File
        {
        protected:
            std::fstream file;
            std::string fpath{};

            File() = default;

            virtual ~File()
            {
                if (file.is_open()) file.close();
            }

            File(const File&) = delete;
            File& operator=(const File&) = delete;

            File(File&& other) : file(std::move(other.file)), fpath(std::move(other.fpath)){};

            File& operator=(File&& other)
            {
                if (&other == this) return *this;
                close();
                file = std::move(other.file);
                fpath = std::move(other.fpath);
                return *this;
            }
        public:
            /**
            * @brief 打开一个文件，失败抛异常
            * @param path：文件路径
            * @note 接口函数
            */
            virtual void open(const std::string &path) = 0;
            /**
            * @brief 关闭当前文件
            * @note 如果关了不会抛异常
            * @note 文件会关闭，而我对她的思念不会.
            */
            void close()
            {
                if (file.is_open()) { fpath = ""; file.close();}
            }
            /**
            * @brief 关闭这个文件，并重新打开
            * @param path：新打开的文件路径
            */
            virtual void reopen(const std::string& path) = 0;

            /**
            * @brief 获取文件是否打开
            * @return true 打开
            * @return false 关闭
            */
            bool is_open() const noexcept
            {
                return file.is_open();
            }
        };
        /**
        * @brief 输入文件类
        */
        class IFile : public File
        {
        public:
            IFile() : File(){}
            /**
            * @brief 构造一个文件并打开，失败抛异常
            * @param path：文件打开时的路径
            */
            explicit IFile(const std::string &path)
            { 
                open(path);
            }
            /**
            * @brief 使用字符串来读取文件所有内容
            * @return std::string 文件所有内容
            */
            virtual void open(const std::string &path) override
            {
                if (file.is_open()) throw std::runtime_error("Please close the file.");
                file.open(path, std::ios::in);
                if (!file.is_open()) throw std::runtime_error("File open error.");
                fpath = path;
            }
            std::string read_all_text()
            {
                if (!file.is_open())
                {
                    throw std::runtime_error("File reading error.");
                }
                //去掉错误信息
                file.clear();
                //核心内容:
                std::string text{};
                std::string line{};
                while(std::getline(file, line))
                {
                    text+=(line + '\n');
                }
                if ((!text.empty()) && text[text.size() - 1] == '\n') { text.pop_back(); }
                //判断是否成功
                if (!file.bad())
                    return text;
                else throw std::runtime_error("The file reading error.");
            }
            virtual void reopen(const std::string &path) override
            {
                if (file.is_open()) file.close();
                file.open(path, std::ios::in);
                if (file.is_open()) { fpath = path; return; }
                else throw std::runtime_error("File open error.");
            }
        };
        /**
        * @brief 覆盖输出文件类
        */
        class OTFile : public File
        {
        public:
            OTFile() : File(){}
            /**
            * @brief 构造一个文件并打开，失败抛异常
            * @param path：文件打开时的路径
            */
            explicit OTFile(const std::string &path)
            { 
                open(path);
            }
            /**
            * @brief 用字符串输出文件
            * @param text 要输出的内容(覆盖)
            */

            virtual void open(const std::string &path) override
            {
                if (file.is_open()) throw std::runtime_error("Please close the file.");
                file.open(path, std::ios::out | std::ios::trunc);
                if (!file.is_open()) throw std::runtime_error("File open error.");
                fpath = path;
            }

            void write_all_text(const std::string &text)
            {
                if (!file.is_open())
                {
                    throw std::runtime_error("File output error.");
                }
                file.clear();
                file << text;
                file.flush();//刷新确保写入
                if (!file.fail())
                    return;
                else
                    throw std::runtime_error("The file output error.");
            }
            /**
            * @brief 关闭这个文件，并重新打开
            * @param path：新打开的文件路径
            */
            virtual void reopen(const std::string &path) override
            {
                if (file.is_open()) file.close();
                file.open(path, std::ios::trunc | std::ios::out);
                if (file.is_open()) { fpath = path; return; }
                else throw std::runtime_error("File open error.");
            }
        };
        /**
        * @brief 追加输出文件类
        */
        class OTAFile : public File
        {
        public:
            OTAFile() : File(){}
            /**
            * @brief 构造一个文件并打开，失败抛异常
            * @param path：文件打开时的路径
            */
            explicit OTAFile(const std::string &path)
            { 
                open(path);
            }
            /**
            * @brief 用字符串输出文件
            * @param text 要输出的内容(覆盖)
            */

            virtual void open(const std::string &path) override
            {
                if (file.is_open()) throw std::runtime_error("Please close the file.");
                file.open(path, std::ios::app);
                if (!file.is_open()) throw std::runtime_error("File open error.");
                fpath = path;
            }   

            /**
            * @brief 追加文件内容
            * @param text：要追加的内容
            */
            void append_all_text(const std::string &text)
            {
                if (!file.is_open())
                {
                    throw std::runtime_error("File append error.");
                }
                file.clear();//清空错误状态
                file << text;
                if (file.fail())
                {
                    throw std::runtime_error("The file output error.");
                }
                file.flush();//刷新确保写入
            }
            /**
            * @brief 关闭这个文件，并重新打开
            * @param path：新打开的文件路径
            */
            virtual void reopen(const std::string &path) override
            {
                if (file.is_open()) file.close();
                file.open(path, std::ios::app);
                if (file.is_open()) { fpath = path; return; }
                else throw std::runtime_error("File open error.");
            }
        };
        /**
         * @brief 一个智能快速文件处理类
         */
        class QuickFile
        {
        public:
            /**
            * @brief 读取文件内容
            * @param path：文件路径
            * @return std::string：文件内容
            */
            static std::string read_all_text(const std::string &path)
            {
                std::string text{};
                std::string line{};
                std::ifstream file;
                file.open(path);
                if (!file.is_open()) throw std::runtime_error("File open error.");
                while (std::getline(file, line)) 
                {
                    text += ( line + '\n');
                }
                if (!text.empty() && text[text.size() - 1] == '\n') text.pop_back();
                return text;
            }
            /**
            * @brief 追加文件内容
            * @param text：要追加的内容
            * @param path：文件路径
            */
            static void add_all_text(const std::string &path, const std::string &text)
            {
                std::ofstream file;
                file.open(path, std::ios::app);
                if (!file.is_open()) throw std::runtime_error("File open error.");
                file << text;
                if (!file.fail()) return;
                else throw std::runtime_error("Add file text error.");   
            }
            /**
            * @brief 覆盖写入文件内容
            * @param text：要写入的内容
            * @param path：文件路径
            */
            static void write_all_text(const std::string &path, const std::string &text)
            {
                std::ofstream file;
                file.open(path, std::ios::trunc | std::ios::out);
                if (!file.is_open()) throw std::runtime_error("File open error.");
                file << text;
                if (!file.fail()) return;
                else throw std::runtime_error("Write file text error.");   
            }
        };
    }
    using quick_file = file::QuickFile;
}

#endif