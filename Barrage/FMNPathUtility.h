/************************************************************************/
/*	Copyright (c) 2015 FMN. All rights reserved.                        */
/************************************************************************/
#pragma once
#include <string>


/** ·����ȡ������ 
*/
class FMNPathUtility
{
public:
    /** ��ȡ��ǰִ��exe��·�� 
    */
    static bool GetExeFilePath(std::wstring &pPath, const wchar_t *pSubPath = nullptr);


private:
    FMNPathUtility() {}
    ~FMNPathUtility() {}
};

