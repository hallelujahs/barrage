/************************************************************************/
/*	Copyright (c) 2015 FMN. All rights reserved.                        */
/************************************************************************/
#include "FMNBarrageGetter.h"
#include <curl/curl.h>
#include <boost/property_tree/ptree.hpp>


static size_t OnWriteData(void* buffer, size_t size, size_t nmemb, void* lpVoid)
{
    std::string* str = dynamic_cast<std::string*>((std::string *)lpVoid);
    if (NULL == str || NULL == buffer)
    {
        return -1;
    }

    char* pData = (char*)buffer;
    str->append(pData, size * nmemb);
    return nmemb;
}


FMNBarrageGetter::FMNBarrageGetter(FMNUrl const& url)
    : m_url(url)
{

}


int FMNBarrageGetter::GetBarrage(FMNBarrageStrVec& barrageVec)
{
    CURLcode res;
    CURL* curl = curl_easy_init();
    if (NULL == curl)
    {
        return CURLE_FAILED_INIT;
    }

    std::string getStr;

    curl_easy_setopt(curl, CURLOPT_URL, m_url.c_str());
    curl_easy_setopt(curl, CURLOPT_READFUNCTION, NULL);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, OnWriteData);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&getStr);
    /**
    * 当多个线程都使用超时处理的时候，同时主线程中有sleep或是wait等操作。
    * 如果不设置这个选项，libcurl将会发信号打断这个wait从而导致程序退出。
    */
    curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);
    curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 3);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 3);
    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    return res;
}
