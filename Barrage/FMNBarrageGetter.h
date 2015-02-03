/************************************************************************/
/*	Copyright (c) 2015 FMN. All rights reserved.                        */
/************************************************************************/
#pragma once
#include <string>
#include <vector>


typedef std::wstring FMNBarrageStr;
typedef std::vector<FMNBarrageStr> FMNBarrageStrVec;


class FMNBarrageGetter
{
    typedef std::string FMNUrl;
public:
    FMNBarrageGetter(FMNUrl const& url);


    /**
    * @brief HTTP GET请求
    * @param strResponse 输出参数,返回的内容
    * @return 返回是否Post成功
    */
    int GetBarrage(FMNBarrageStrVec& barrageVec);


private:
    FMNUrl  m_url;
};

