/************************************************************************/
/*	Copyright (c) 2015 FMN. All rights reserved.                        */
/************************************************************************/
#include <tchar.h>
#include <Windows.h>
#include "FMNPathUtility.h"


bool FMNPathUtility::GetExeFilePath(std::wstring &pPath, 
    const wchar_t *pSubPath /* = nullptr */)
{
    wchar_t szPath[MAX_PATH];
    if (!::GetModuleFileName(NULL, szPath, MAX_PATH))
    {
        return false;
    }
    (_tcsrchr(szPath, '\\'))[1] = '\0';
    pPath = szPath;

    if (nullptr != pSubPath)
    {
        pPath += pSubPath;
    }
    return true;
}

