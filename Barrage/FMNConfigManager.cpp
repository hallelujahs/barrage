/************************************************************************/
/*	Copyright (c) 2015 FMN. All rights reserved.                        */
/************************************************************************/
#include "FMNConfigManager.h"
#include "FMNPathUtility.h"
#include <Windows.h>
#include <Shlwapi.h>
#include <ShlObj.h>
#include <fstream>


wchar_t const* const FMN_CONFIG_FILE_NAME = L"FMNBarrage.conf";


FMNConfigManagerImpl::FMNConfigManagerImpl() 
    : Config()
{
    LoadConfig();
}


FMNConfigManagerImpl::~FMNConfigManagerImpl()
{
    SaveConfig();
}


bool FMNConfigManagerImpl::LoadConfig()
{
    // ��ȡ�����ļ�����
    std::wstring configPath;
    if (!FMNPathUtility::GetExeFilePath(configPath, FMN_CONFIG_FILE_NAME))
    {
        return false;
    }

    // �ж��ļ��Ƿ���ڣ�������ֱ�Ӵ���
    if (!::PathFileExists(configPath.c_str()))
    {
        return SaveConfigFile(configPath);
    }

    // ����ļ��Ѵ��ڣ������
    std::wifstream ifs(configPath);
    if (!ifs.good())
    {
        return false;
    }

    boost::archive::xml_wiarchive ia(ifs);
    ia >> BOOST_SERIALIZATION_NVP(Config);
    ifs.close();
    return true;
}


bool FMNConfigManagerImpl::SaveConfig()
{
    // ��ȡ�����ļ�����
    std::wstring configPath;
    if (!FMNPathUtility::GetExeFilePath(configPath, FMN_CONFIG_FILE_NAME))
    {
        return false;
    }

    // ���������ļ�
    return SaveConfigFile(configPath);
}


bool FMNConfigManagerImpl::SaveConfigFile(FMNConfigFile const& configFile)
{
    std::wofstream ofs(configFile);
    if (!ofs.good())
    {
        return false;
    }

    boost::archive::xml_woarchive oa(ofs);
    oa << BOOST_SERIALIZATION_NVP(Config);
    ofs.close();
    return true;
}

