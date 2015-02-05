/************************************************************************/
/*	Copyright (c) 2015 FMN. All rights reserved.                        */
/************************************************************************/
#pragma once
#include <string>
#include <vector>
#include <future>


class QMutex;


typedef std::wstring FMNBarrageStr;
typedef std::vector<FMNBarrageStr> FMNBarrageStrVec;


/** ��ĻHTTP��ȡ�� 
*/
class FMNBarrageGetter
{
public:
    FMNBarrageGetter(QMutex* pMutex, FMNBarrageStrVec* pBarrageStrVec);


    ~FMNBarrageGetter();


    /**
    * @brief 
    * @param strResponse �������,���ص�����
    * @return �����Ƿ�Post�ɹ�
    */
    bool GetBarrage();


    /** HTTP GET����
    @param [in] 
    @param [in] 
    @param [out] 
    @return 
    */
    int GetHttpJson(std::string& getStr);


private:
    /** �Ƿ������ȡ����
    */
    bool                m_isEndGetter;
    /** ��ȡ����ͬ���ź��� 
    */
    QMutex*             m_barrageMutex;
    /** ��ȡ���ݴ洢λ�� 
    */
    FMNBarrageStrVec*   m_barrageStrVec;
    /** ��ȡ�����߳� 
    */
    std::future<void>   m_barrageGetterThread;
};

