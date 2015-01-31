/************************************************************************/
/*	Copyright (c) 2015 FMN. All rights reserved.                        */
/************************************************************************/
#pragma once


/** 保证进程唯一实例 
*/
class FMNUniqueProgress
{
public:
    /** 创建唯一实例标示 
    */
    static bool CreateUniqueProgress(const wchar_t* pProgressName);

    
protected:
    FMNUniqueProgress() {}
    ~FMNUniqueProgress() {}
};

