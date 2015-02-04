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




/** �����ļ�������Ϣ 
*/
struct FMNConfig
{
    FMN_SERIALIZE_NVP_9(MoveSpeed, MoveSpeedAdjust, GetBarrageSpeed, ShowLineCount, 
        LineTolerance, FontSize, FontColors, FontFamily, ServerUrl);

    typedef std::vector<Qt::GlobalColor>    FMNColorVec;
    typedef std::wstring                    FMNFontFamily;
    typedef std::string                     FMNUrl;


    /** �ƶ��ٶ� 
    */
    int             MoveSpeed;
    /** �ƶ��ٶȵ���ֵ 
    */
    int             MoveSpeedAdjust;
    /** ��ȡ��Ļʱ���� 
    */
    int             GetBarrageSpeed;
    /** ���ֵ����� 
    */
    int             ShowLineCount;
    /** �ݲ�ֵ��С 
    */
    int             LineTolerance;
    /** �����С 
    */
    int             FontSize;
    /** ���Գ��ֵ���ɫ 
    */
    FMNColorVec     FontColors;
    /** ���� 
    */
    FMNFontFamily   FontFamily;
    /** ��������ַ 
    */
    FMNUrl          ServerUrl;


    /** ���캯�� 
    */
    FMNConfig();


    /** ���캯��
    */
    FMNConfig(int moveSpeed, int moveSpeedAdjust, int getBarrageSpeed, 
        int showLineCount, int lineTolerance, int fontSize, FMNColorVec const& fontColors, 
        FMNFontFamily const& fontFamily, FMNUrl const& serverUrl);


    /** ��������
    */
    FMNConfig(FMNConfig const& config);


    /** ��ֵ���� 
    */
    FMNConfig& operator=(FMNConfig const& config);
};

