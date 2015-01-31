/************************************************************************/
/*	Copyright (c) 2015 FMN. All rights reserved.                        */
/************************************************************************/
#pragma once
#include "FMNConfig.h"
#include "FMNSingleton.h"


/** 配置文件管理器 
*/
class FMNConfigManagerImpl
{
    typedef std::wstring FMNConfigFile;
public:
    /** 构造函数 
    */
    FMNConfigManagerImpl();


    /** 析构函数 
    */
    ~FMNConfigManagerImpl();


    /** 获取配置信息 
    @return 配置信息
    */
    FMNConfig& GetConfig() { return Config; }


    /** 加载配置文件
    @param [in] solutionFile 配置文件路径
    @return true 加载成功\n
            false 加载失败
    */
    bool LoadConfig();


    /** 保存配置信息
    @param [in] solutionFile 保存到的路径，不为空为另存为
    @return true 保存成功\n
            false 保存失败
    */
    bool SaveConfig();


protected:
    /** 保存配置文件
    @param [in] configFile 配置文件
    @return true 保存成功\n
            false 保存失败
    */
    bool SaveConfigFile(FMNConfigFile const& configFile);


private:
    /** 配置信息 
    */
    FMNConfig       Config;
};


typedef FMNSingleton<FMNConfigManagerImpl>    FMNConfigManager;

