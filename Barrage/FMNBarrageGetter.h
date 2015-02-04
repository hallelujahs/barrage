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
    * @param strResponse �������,���ص�����
    * @return �����Ƿ�Post�ɹ�
    */
    bool GetBarrage(FMNBarrageStrVec& barrageVec);


    /** HTTP GET����
    @param [in] 
    @param [in] 
    @param [out] 
    @return 
    */
    int GetHttpJson(std::string& getStr);


private:
    QMutex*     m_barrageMutex;

};

