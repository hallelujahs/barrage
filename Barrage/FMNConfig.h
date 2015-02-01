/************************************************************************/
/*	Copyright (c) 2015 FMN. All rights reserved.                        */
/************************************************************************/
#pragma once
#include <vector>
#include <string>
#include <QtCore/qnamespace.h>
#include "FMNDataSerialize.h"


/** ʹ�õ���ɫ���� 
*/
enum FMNColorType
{
    FMN_COLOR_RED           = Qt::red,
    FMN_COLOR_GREEN         = Qt::green,
    FMN_COLOR_BLUE          = Qt::blue,
    FMN_COLOR_CYAN          = Qt::cyan,
    FMN_COLOR_MAGENTA       = Qt::magenta,
    FMN_COLOR_YELLOW        = Qt::yellow,
    FMN_COLOR_DARKRED       = Qt::darkRed,
    FMN_COLOR_DARKGREEN     = Qt::darkGreen,
    FMN_COLOR_DARKBLUE      = Qt::darkBlue,
    FMN_COLOR_DARKCYAN      = Qt::darkCyan,
    FMN_COLOR_DARKMAGENTA   = Qt::darkMagenta,
    FMN_COLOR_DARKYELLOW    = Qt::darkYellow,
};


/** �����ļ�������Ϣ 
*/
struct FMNConfig
{
    FMN_SERIALIZE_NVP_8(MoveSpeed, MoveSpeedAdjustCharCount, MoveSpeedAdjust, GetBarrageSpeed, ShowLineCount, FontSize, FontColors, FontFamily);

    typedef std::vector<int>    FMNColorVec;
    typedef std::wstring        FMNFontFamily;


    /** �ƶ��ٶ� 
    */
    int             MoveSpeed;
    /** ������Ŀ�ٶȵ���ֵ
    */
    int             MoveSpeedAdjustCharCount;
    /** �ƶ��ٶȵ���ֵ 
    */
    int             MoveSpeedAdjust;
    /** ��ȡ��Ļʱ���� 
    */
    int             GetBarrageSpeed;
    /** ���ֵ����� 
    */
    int             ShowLineCount;
    /** �����С 
    */
    int             FontSize;
    /** ���Գ��ֵ���ɫ 
    */
    FMNColorVec     FontColors;
    /** ���� 
    */
    FMNFontFamily   FontFamily;


    /** ���캯�� 
    */
    FMNConfig();


    /** ���캯��
    */
    FMNConfig(int moveSpeed, int moveSpeedAdjustCharCnt, int moveSpeedAdjust, 
        int getBarrageSpeed, int showLineCount, int fontSize, 
        FMNColorVec const& fontColors, FMNFontFamily const& fontFamily);


    /** ��������
    */
    FMNConfig(FMNConfig const& config);


    /** ��ֵ���� 
    */
    FMNConfig& operator=(FMNConfig const& config);
};


