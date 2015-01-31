/************************************************************************/
/*	Copyright (c) 2015 FMN. All rights reserved.                        */
/************************************************************************/
#pragma once
#include "FMNConfig.h"
#include "FMNSingleton.h"


/** �����ļ������� 
*/
class FMNConfigManagerImpl
{
    typedef std::wstring FMNConfigFile;
public:
    /** ���캯�� 
    */
    FMNConfigManagerImpl();


    /** �������� 
    */
    ~FMNConfigManagerImpl();


    /** ��ȡ������Ϣ 
    @return ������Ϣ
    */
    FMNConfig& GetConfig() { return Config; }


    /** ���������ļ�
    @param [in] solutionFile �����ļ�·��
    @return true ���سɹ�\n
            false ����ʧ��
    */
    bool LoadConfig();


    /** ����������Ϣ
    @param [in] solutionFile ���浽��·������Ϊ��Ϊ���Ϊ
    @return true ����ɹ�\n
            false ����ʧ��
    */
    bool SaveConfig();


protected:
    /** ���������ļ�
    @param [in] configFile �����ļ�
    @return true ����ɹ�\n
            false ����ʧ��
    */
    bool SaveConfigFile(FMNConfigFile const& configFile);


private:
    /** ������Ϣ 
    */
    FMNConfig       Config;
};


typedef FMNSingleton<FMNConfigManagerImpl>    FMNConfigManager;

