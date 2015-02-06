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


/** 弹幕HTTP获取器 
*/
class FMNBarrageGetter
{
public:
    FMNBarrageGetter(QMutex* pMutex, FMNBarrageStrVec* pBarrageStrVec);


    ~FMNBarrageGetter();


    void SetPause(bool isPause)
    {m_isPause = isPause;}


    /**
    * @brief 
    * @param strResponse 输出参数,返回的内容
    * @return 返回是否Post成功
    */
    bool GetBarrage();


    /** HTTP GET请求
    @param [in] 
    @param [in] 
    @param [out] 
    @return 
    */
    int GetHttpJson(std::string& getStr);


private:
    /** 是否暂停 
    */
    bool                m_isPause;
    /** 是否结束获取数据
    */
    bool                m_isEndGetter;
    /** 获取数据同步信号量 
    */
    QMutex*             m_barrageMutex;
    /** 获取数据存储位置 
    */
    FMNBarrageStrVec*   m_barrageStrVec;
    /** 获取数据线程 
    */
    std::future<void>   m_barrageGetterThread;
};

