/************************************************************************/
/*	Copyright (c) 2015 FMN. All rights reserved.                        */
/************************************************************************/
#pragma once
#include <string>
#include <vector>


class QMutex;


typedef std::wstring FMNBarrageStr;
typedef std::vector<FMNBarrageStr> FMNBarrageStrVec;


class FMNBarrageGetter
{
public:
    FMNBarrageGetter(QMutex* pMutex);


    /**
    * @brief 
    * @param strResponse 输出参数,返回的内容
    * @return 返回是否Post成功
    */
    bool GetBarrage(FMNBarrageStrVec& barrageVec);


    /** HTTP GET请求
    @param [in] 
    @param [in] 
    @param [out] 
    @return 
    */
    int GetHttpJson(std::string& getStr);


private:
    QMutex*     m_barrageMutex;

};

