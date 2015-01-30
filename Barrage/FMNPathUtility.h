/************************************************************************/
/*	Copyright (c) 2015 FMN. All rights reserved.                        */
/************************************************************************/
#pragma once
#include <string>


/** 路径获取基础类 
*/
class FMNPathUtility
{
public:
    /** 获取当前执行exe的路径 
    */
    static bool GetExeFilePath(std::wstring &pPath, const wchar_t *pSubPath = nullptr);


private:
    FMNPathUtility() {}
    ~FMNPathUtility() {}
};

