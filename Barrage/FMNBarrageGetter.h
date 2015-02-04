/************************************************************************/
/*	Copyright (c) 2015 FMN. All rights reserved.                        */
/************************************************************************/
#pragma once
#include <string>
#include <vector>


typedef std::string FMNBarrageStr;
typedef std::vector<FMNBarrageStr> FMNBarrageStrVec;


class FMNBarrageGetter
{
public:
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


};

