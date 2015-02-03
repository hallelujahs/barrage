/************************************************************************/
/*	Copyright (c) 2015 FMN. All rights reserved.                        */
/************************************************************************/
#include "FMNConfig.h"


int const MOVE_SPEED                    = 10;
int const MOVE_SPEED_ADJUST             = 5;
int const GET_BARRAGE_SPEED             = 1000;
int const SHOW_LINE_COUNT               = 10;
int const LINE_TOLERANCE                = 5;
int const FONT_SIZE                     = 30;
wchar_t const* const FONT_FAMILY        = L"ºÚÌå";


FMNConfig::FMNConfig()
    : MoveSpeed(MOVE_SPEED), GetBarrageSpeed(GET_BARRAGE_SPEED), 
    MoveSpeedAdjust(MOVE_SPEED_ADJUST), ShowLineCount(SHOW_LINE_COUNT), 
    LineTolerance(LINE_TOLERANCE), FontSize(FONT_SIZE), FontColors(),
    FontFamily(FONT_FAMILY)
{
    FontColors.push_back(Qt::red);
}


FMNConfig::FMNConfig(int moveSpeed, int moveSpeedAdjust,
    int getBarrageSpeed, int showLineCount, int lineTolerance, int fontSize,
    FMNColorVec const& fontColors, FMNFontFamily const& fontFamily)
    : MoveSpeed(moveSpeed), MoveSpeedAdjust(moveSpeedAdjust), GetBarrageSpeed(getBarrageSpeed), 
    ShowLineCount(showLineCount), LineTolerance(lineTolerance), FontSize(fontSize), 
    FontColors(fontColors), FontFamily(fontFamily)
{

}


FMNConfig::FMNConfig(FMNConfig const& config)
    : MoveSpeed(config.MoveSpeed), MoveSpeedAdjust(config.MoveSpeedAdjust), 
    GetBarrageSpeed(config.GetBarrageSpeed),ShowLineCount(config.ShowLineCount), 
    LineTolerance(config.LineTolerance), FontSize(config.FontSize), 
    FontColors(config.FontColors), FontFamily(config.FontFamily)
{

}


FMNConfig& FMNConfig::operator=(FMNConfig const& config)
{
    MoveSpeed = config.MoveSpeed;
    MoveSpeedAdjust = config.MoveSpeedAdjust;
    GetBarrageSpeed = config.GetBarrageSpeed;
    ShowLineCount = config.ShowLineCount;
    LineTolerance = config.LineTolerance;
    FontSize = config.FontSize;
    FontColors = config.FontColors;
    FontFamily = config.FontFamily;
    return (*this);
}

