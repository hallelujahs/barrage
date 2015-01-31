/************************************************************************/
/*	Copyright (c) 2015 FMN. All rights reserved.                        */
/************************************************************************/
#pragma once


/** ����ģʽ 
*/
template <class T>
class FMNSingleton
{
public:
    /** ��ȡ����ָ��
    @return ����ָ��
    */
    static T* GetInstance()
    {
        if (m_instance == nullptr)
        {
            m_instance = new(std::nothrow) T;
        }
        return m_instance;
    }


    /** �ͷŵ��� 
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
    /** ���캯�� 
    */
    FMNSingleton() {};


    /** �������� 
    */
    virtual ~FMNSingleton() {};


private:
    /** ����ָ�� 
    */
    static T*   m_instance;
};


/** ����ָ������ 
*/
template <class T>
T* FMNSingleton<T>::m_instance = nullptr;

