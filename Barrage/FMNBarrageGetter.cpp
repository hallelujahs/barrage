/************************************************************************/
/*	Copyright (c) 2015 FMN. All rights reserved.                        */
/************************************************************************/
#include "FMNBarrageGetter.h"
#include "FMNConfigManager.h"
#include <curl/curl.h>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/program_options/detail/convert.hpp>
#include <boost/program_options/detail/utf8_codecvt_facet.hpp>
#include <boost/foreach.hpp>
#include <QtCore/QMutex>
#include <sstream>
#include <codecvt>
#include <Windows.h>


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


FMNBarrageGetter::FMNBarrageGetter(QMutex* pMutex, FMNBarrageStrVec* pBarrageStrVec)
    : m_barrageMutex(pMutex), m_barrageStrVec(pBarrageStrVec), m_isEndGetter(false)
{
    m_barrageGetterThread = std::async(std::launch::async, [&]()
    {
        int sleepTime = FMNConfigManager::GetInstance()->GetConfig().GetBarrageSpeed;
        while (!m_isEndGetter)
        {
            GetBarrage();
            Sleep(sleepTime);
        }
    });
}


FMNBarrageGetter::~FMNBarrageGetter()
{
    m_isEndGetter = true;
    m_barrageGetterThread.wait();
}


bool FMNBarrageGetter::GetBarrage()
{
    std::string jsonStr;
    if (CURLE_OK != GetHttpJson(jsonStr))
    {
        return false;
    }

    if (jsonStr.length() < 3)
    {
        return true;
    }

    std::wstringstream ss(std::wstring(jsonStr.begin(), jsonStr.end()));
    std::locale utf8Locale(std::locale(),
        new boost::program_options::detail::utf8_codecvt_facet());
    ss.imbue(utf8Locale);

    boost::property_tree::wptree pt;
    try
    {
        boost::property_tree::read_json(ss, pt);

        QMutexLocker mutexLocker(m_barrageMutex);
        BOOST_FOREACH(const boost::property_tree::wptree::value_type &v, pt)
        {
            std::wstringstream parseStream;
            parseStream << v.second.data();
            m_barrageStrVec->push_back(parseStream.str());
        }
    }
    catch (...)
    {
        return false;
    }

    return true;
}


int FMNBarrageGetter::GetHttpJson(std::string& getStr)
{
    FMNConfig &config = FMNConfigManager::GetInstance()->GetConfig();
    CURLcode res;
    CURL* curl = curl_easy_init();
    if (NULL == curl)
    {
        return CURLE_FAILED_INIT;
    }

    curl_easy_setopt(curl, CURLOPT_URL, config.ServerUrl.c_str());
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

