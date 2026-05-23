#include <iostream>
#include <string>
#include <easyx.h>

#include "mathpp.h"


// 窗口常量
constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 600;
constexpr int X_OFFSET = WINDOW_WIDTH / 2;
constexpr int Y_OFFSET = WINDOW_HEIGHT / 2;

int main()
{
    initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);

    // 一次函数参数 y = kx + b
    int k = 1;
    int b = 0;

    pp::math::MathFunction<int, int> mf([&k, &b](int x)->int {
        return k * x + b;
    });

    while (true)
    {
        auto pkg = pp::math::sample(mf, -400, 800, 1).get_pack();

        BeginBatchDraw();
        cleardevice();

        // 画坐标系
        setlinecolor(WHITE);
        line(0, Y_OFFSET, WINDOW_WIDTH, Y_OFFSET);
        line(X_OFFSET, 0, X_OFFSET, WINDOW_HEIGHT);

        // 画函数图像
        setlinecolor(RED);
        setlinestyle(PS_SOLID, 2);

        for (size_t i = 0; i < pkg.size() - 1; ++i)
        {
            int x1 = X_OFFSET + pkg[i].first;
            int y1 = WINDOW_HEIGHT - pkg[i].second - Y_OFFSET;
            int x2 = X_OFFSET + pkg[i + 1].first;
            int y2 = WINDOW_HEIGHT - pkg[i + 1].second - Y_OFFSET;
            line(x1, y1, x2, y2);
        }

        // 界面文字显示
        settextcolor(WHITE);
        settextstyle(20, 0, _T("宋体"));

        std::string k_info = "k: " + std::to_string(k);
        std::string b_info = "b: " + std::to_string(b);
        std::string fn = "y = " + std::to_string(k) + "x + " + std::to_string(b);

        outtextxy(10, 10, k_info.c_str());
        outtextxy(10, 50, b_info.c_str());
        // outtextxy(10, 90, _T("操作指南: K 键：k++  L 键：k--"));
        // outtextxy(10, 130, _T("操作指南: B 键：b++  N 键：b--"));
        outtextxy(10, 90, fn.c_str());

        EndBatchDraw();

        // 按键控制
        if (GetAsyncKeyState('K')) { k++; }
        if (GetAsyncKeyState('L')) { k--; }
        if (GetAsyncKeyState('B')) { b += 10; }
        if (GetAsyncKeyState('N')) { b -= 10; }

        // ESC 退出
        if (GetAsyncKeyState(VK_ESCAPE)) break;

        Sleep(16);
    }

    closegraph();
    return 0;
}