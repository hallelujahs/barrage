/************************************************************************/
/*	Copyright (c) 2015 FMN. All rights reserved.                        */
/************************************************************************/
#pragma once
#include <vector>
#include <string>
#include <QtCore/qnamespace.h>
#include "FMNDataSerialize.h"


/** 使用的颜色类型 
*/
//enum FMNColorType
//{
//    FMN_COLOR_RED           = Qt::red,
//    FMN_COLOR_GREEN         = Qt::green,
//    FMN_COLOR_BLUE          = Qt::blue,
//    FMN_COLOR_CYAN          = Qt::cyan,
//    FMN_COLOR_MAGENTA       = Qt::magenta,
//    FMN_COLOR_YELLOW        = Qt::yellow,
//    FMN_COLOR_DARKRED       = Qt::darkRed,
//    FMN_COLOR_DARKGREEN     = Qt::darkGreen,
//    FMN_COLOR_DARKBLUE      = Qt::darkBlue,
//    FMN_COLOR_DARKCYAN      = Qt::darkCyan,
//    FMN_COLOR_DARKMAGENTA   = Qt::darkMagenta,
//    FMN_COLOR_DARKYELLOW    = Qt::darkYellow,
//};




/** 配置文件保存信息 
*/
struct FMNConfig
{
    FMN_SERIALIZE_NVP_9(MoveSpeed, MoveSpeedAdjust, GetBarrageSpeed, ShowLineCount, 
        LineTolerance, FontSize, FontColors, FontFamily, ServerUrl);

    typedef std::vector<Qt::GlobalColor>    FMNColorVec;
    typedef std::wstring                    FMNFontFamily;
    typedef std::string                     FMNUrl;


    /** 移动速度 
    */
    int             MoveSpeed;
    /** 移动速度调整值 
    */
    int             MoveSpeedAdjust;
    /** 获取弹幕时间间隔 
    */
    int             GetBarrageSpeed;
    /** 出现的行数 
    */
    int             ShowLineCount;
    /** 容差值大小 
    */
    int             LineTolerance;
    /** 字体大小 
    */
    int             FontSize;
    /** 可以出现的颜色 
    */
    FMNColorVec     FontColors;
    /** 字体 
    */
    FMNFontFamily   FontFamily;
    /** 服务器地址 
    */
    FMNUrl          ServerUrl;


    /** 构造函数 
    */
    FMNConfig();


    /** 构造函数
    */
    FMNConfig(int moveSpeed, int moveSpeedAdjust, int getBarrageSpeed, 
        int showLineCount, int lineTolerance, int fontSize, FMNColorVec const& fontColors, 
        FMNFontFamily const& fontFamily, FMNUrl const& serverUrl);


    /** 拷贝构造
    */
    FMNConfig(FMNConfig const& config);


    /** 赋值函数 
    */
    FMNConfig& operator=(FMNConfig const& config);
};

