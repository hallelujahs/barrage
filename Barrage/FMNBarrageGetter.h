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
    * @brief HTTP GET����
    * @param strResponse �������,���ص�����
    * @return �����Ƿ�Post�ɹ�
    */
    int GetBarrage(FMNBarrageStrVec& barrageVec);


private:
    FMNUrl  m_url;
};

