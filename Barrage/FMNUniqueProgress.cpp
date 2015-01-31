/************************************************************************/
/*	Copyright (c) 2015 FMN. All rights reserved.                        */
/************************************************************************/
#include "FMNUniqueProgress.h"
#include <Windows.h>


bool FMNUniqueProgress::CreateUniqueProgress(const wchar_t* pProgressName)
{
    HANDLE hMutex = ::CreateMutex(NULL, FALSE, pProgressName);

    return !(hMutex == nullptr || ERROR_ALREADY_EXISTS == ::GetLastError());
}

