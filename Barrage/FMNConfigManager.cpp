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
    // 获取配置文件名称
    std::wstring configPath;
    if (!FMNPathUtility::GetExeFilePath(configPath, FMN_CONFIG_FILE_NAME))
    {
        return false;
    }

    // 判断文件是否存在，不存在直接创建
    if (!::PathFileExists(configPath.c_str()))
    {
        return SaveConfigFile(configPath);
    }

    // 如果文件已存在，则加载
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
    // 获取配置文件名称
    std::wstring configPath;
    if (!FMNPathUtility::GetExeFilePath(configPath, FMN_CONFIG_FILE_NAME))
    {
        return false;
    }

    // 保存配置文件
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

