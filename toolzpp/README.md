
# toolzpp - C++ 工具库

一个轻量级、 header-only 的 C++ 工具库，提供日常开发中常用的函数和数据结构。
### 介绍
* 这是我的第一个作品：一个轻量级、 header-only 的 C++ 工具库，提供日常开发中常用的函数和数据结构，例如字符串处理/格
式化，随机数产生，算法等，具体可见项目。本人学习C++3个月，所以有些写的不好的地方，欢迎反馈！

* This is my first work: a lightweight, header-only C++ utility library that provides commonly used functions and data structures for daily development. I am still learning, so there may be some poorly written parts, feedback is welcome!

## 特性

- **Header-only**：只需包含头文件，无需编译
- **C++17** 标准
- **无第三方依赖**
- **命名空间隔离**：所有功能在 `tlz::` 命名空间下

## 快速开始

```c++
#include "toolzpp.h"
#include <iostream>
using tlz::operator<<;

int main() {
    // 字符串处理
    std::string str = "hello world";
    std::cout << tlz::str::upper(str) << std::endl;  // "HELLO WORLD"
    
    // 字符串分割
    auto parts = tlz::str::split("a,b,c", ',');
    
    // 随机数
    tlz::random::Randomer rng;
    int num = rng.randint(1, 100);
    
    // 容器操作
    std::vector<int> vec = {1, 2, 3, 4, 5};
    auto sum = tlz::math::vector_sum(vec);      // 15
    auto avg = tlz::math::average(vec);         // 3.0
    
    // 输出 vector
    std::cout << vec << std::endl;               // [1,2,3,4,5]
    
    return 0;
}
```
## 模块
**模块列表**
- 模块	说明
- str	字符串处理：分割、大小写转换、格式化、去空格等
- math	数学计算：求和、平均、中位数、众数、加权平均、函数包等
- random	随机数生成：整数、浮点数、随机选择
- algo	容器算法：map、filter、切片、包含检查
- carray	C 数组工具：转 vector/array/map、查找、反转、打印
- counter	计数器类：自增、自减、比较
- tree	树结构：二叉树、单链表（使用 unique_ptr）
- protector	写保护器：控制变量修改权限
- output	输出重载：vector 流输出
- vec	    向量结构体：Vector2/3/4（仅定义）
- toolzpp 所有文件
- progressbar 进度条
- group   属性/条件组
- stand   代表类
- flager  状态类
'''
## 使用，编译
**使用**
- 直接包含，无需链接
- C++17及以上
- 命名空间: tlz
****************************************************************************
----------------------------------------------------------------------------