/************************************************************************/
/*	Copyright (c) 2015 FMN. All rights reserved.                        */
/************************************************************************/
#pragma once


/** 单例模式 
*/
template <class T>
class FMNSingleton
{
public:
    /** 获取单例指针
    @return 单例指针
    */
    static T* GetInstance()
    {
        if (m_instance == nullptr)
        {
            m_instance = new(std::nothrow) T;
        }
        return m_instance;
    }


    /** 释放单例 
    */
    static void ReleaseInstance()
    {
        if (m_instance != nullptr)
        {
            delete m_instance;
            m_instance = nullptr;
        }
    }


protected:
    /** 构造函数 
    */
    FMNSingleton() {};


    /** 析构函数 
    */
    virtual ~FMNSingleton() {};


private:
    /** 单例指针 
    */
    static T*   m_instance;
};


/** 单例指针声明 
*/
template <class T>
T* FMNSingleton<T>::m_instance = nullptr;

