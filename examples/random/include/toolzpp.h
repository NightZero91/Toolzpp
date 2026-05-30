#ifndef TOOLZPP_H
#define TOOLZPP_H

//运行main_example以开始

/**
 * @file toolzpp.h
 * @date 2026-05-29
 * @author NightZero91
 * @brief 轻量级、 header-only 的 C++ 工具库，提供日常开发中常用的函数和数据结构。
 * @note 欢迎使用Toolzpp C++工具库!很高兴看见您使用这个库!本库已有20个文件，2000行代码!在这里，你能
 * 更快捷的使用C++，Toolzpp源代码拥有完善的注释，如果你有任何疑惑的地方，看源码注释便是最好选择.
 * @note NightZero-编写
 * @note 欢迎使用者对该库提出任何建议!
 */

 /*---------------------------------------------------------------------------------

   _   _   _           _       _     ______                      
 | \ | | (_)         | |     | |   |___  /                      
 |  \| |  _    __ _  | |__   | |_     / /    ___   _ __    ___  
 | . ` | | |  / _` | | '_ \  | __|   / /    / _ \ | '__|  / _ \ 
 | |\  | | | | (_| | | | | | | |_   / /__  |  __/ | |    | (_) |
 |_| \_| |_|  \__, | |_| |_|  \__| /_____|  \___| |_|     \___/ 
               __/ |                                            
              |___/        

 ---------------------------------------------------------------------------------*/


 /*---------------------------------------------------------------------------------
         ,----,                                                                     
      ,/   .`|                                                                     
    ,`   .'  :                         ,--,                                        
  ;    ;     /                       ,--.'|                  ,-.----.   ,-.----.   
.'___,/    ,'     ,---.      ,---.   |  | :           ,----, \    /  \  \    /  \  
|    :     |     '   ,'\    '   ,'\  :  : '         .'   .`| |   :    | |   :    | 
;    |.';  ;    /   /   |  /   /   | |  ' |      .'   .'  .' |   | .\ : |   | .\ : 
`----'  |  |   .   ; ,. : .   ; ,. : '  | |    ,---, '   ./  .   : |: | .   : |: | 
    '   :  ;   '   | |: : '   | |: : |  | :    ;   | .'  /   |   |  \ : |   |  \ : 
    |   |  '   '   | .; : '   | .; : '  : |__  `---' /  ;--, |   : .  | |   : .  | 
    '   :  |   |   :    | |   :    | |  | '.'|   /  /  / .`| :     |`-' :     |`-' 
    ;   |.'     \   \  /   \   \  /  ;  :    ; ./__;     .'  :   : :    :   : :    
    '---'        `----'     `----'   |  ,   /  ;   |  .'     |   | :    |   | :    
                                      ---`-'   `---'         `---'.|    `---'.|                                                             `---`      `---` 
 ---------------------------------------------------------------------------------*/

//版本信息
#define TOOLZPP_VERSION_MAJOR 0
#define TOOLZPP_VERSION_MINOR 2
#define TOOLZPP_VERSION_PATCH 0
#define TOOLZPP_VERSION "0.2.0"
//是否为测试版
#define TOOLZPP_BETA 1
//版本日期编号
#define TOOLZPP_DATE 20260529
//包含所有文件
#include "algopp.h"
#include "carraypp.h"
#include "counterpp.h"
#include "flagerpp.h"
#include "grouppp.h"
#include "loadingcircpp.h"
#include "loggerpp.h"
#include "mathpp.h"
#include "mempp.h"
#include "outputpp.h"
#include "progressbarpp.h"
#include "protectorpp.h"
#include "randompp.h"
#include "rangepp.h"
#include "sentencepp.h"
#include "standpp.h"
#include "strpp.h"
#include "treepp.h"
#include "vectorpp.h"

#endif