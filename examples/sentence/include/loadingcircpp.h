#ifndef LOADINGCIRCPP_H
#define LOADINGCIRCPP_H
/**
 * @file loadingcirc.h
 * @date 2026-05-22
 * @author NightZero91
 * @brief 一个简单的转圈类，适合在cmd小工具里模拟加载，属于cmdui板块的一部分
 * @note 欢迎使用者对该文件提出任何建议
 * @warning 多线程请确保加锁
 */
#include <array>
#include <iostream>
#include <ostream>
namespace tlz 
{
    namespace cmdui 
    {
        //动画总帧数
        static constexpr int FRAME = 8;
        /**
        *@brief 转圈加载动画类
        */
        class LoadingCirc
        {
        private:
            //数组储存动画
            std::array<char, FRAME> animations 
            { '-', '/', '|', '\\', '-', '/', '|', '\\'};
            //动画所播放的帧索引
            int idx = 0;
        public:
            LoadingCirc() = default;
            /**
            *@brief 旋转这个圈
            *@note 这就是个十分简单的转圈函数ZZZ
            */
            void rotate() noexcept
            {
                idx++;
                if (idx >= FRAME) idx = 0;
            }
            /**
            *@brief 输出这个圈到控制台(覆盖)
            */
            void print() const
            {
                std::cout << '\r' << animations[idx] << std::flush;
            }
            /**
            *@brief 使用ostream输出的重载
            */
            friend std::ostream& operator<<(std::ostream &o, const LoadingCirc& circ)
            {
                o << circ.animations[circ.idx];
                return o;
            }
            /**
            *@brief 获取播放到的帧索引
            *@return 索引
            */
            int get_frame() const noexcept
            {
                return idx;
            }
        };
    }
}

#endif