/************************************************************************/
/*	Copyright (c) 2015 FMN. All rights reserved.                        */
/************************************************************************/
#pragma once
#include "FMNBarrageItem.h"
#include "FMNBarrageGetter.h"
#include <QtCore/QTimer>
#include <QtCore/QMutex>
#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSystemTrayIcon>
#include <vector>


class QToolButton;
class QVBoxLayout;
class FMNSystemTrayMenu;
class FMNBarrageItem;


/** ��Ļ���� 
*/
class FMNBarrage : public QWidget
{
    Q_OBJECT
public:
    /** ���캯�� 
    */
    FMNBarrage(QWidget *parent = 0);


    /** �������� 
    */
    ~FMNBarrage();



public slots:
    /** ��ʾ�벻��ʾ�л��¼�
    */
    void OnShowCtrlBtn();


    /** �ӷ������˻�ȡ����
    */
    void OnGetData();


    /** ��ӵ�Ļ 
    */
    void AddBarrageItem();


protected:
    /** ��ȡ��һ����Ļ��ʾ��λ��
    @param [in] 
    @param [in] 
    @param [out] 
    @return 
    */
    bool GetNextBarrageItemPos(int& posY);


    void RemoveShowedItem();


    void RemoveAllItem();


private:
    /** �Ƿ���ʾ 
    */
    bool                m_isShow;
    /** ����ͼ��
    */
    QSystemTrayIcon     *m_systemTrayIcon;
    /** ���̲˵� 
    */
    FMNSystemTrayMenu   *m_systemTrayMenu;
    /** ��ʾ�ͷ���ʾ��ť 
    */
    QToolButton         *m_showCtrlBtn;
    /** ���岼�� 
    */
    QVBoxLayout         *m_layout;
    /** ���ݻ�ȡ��ʱ�� 
    */
    QTimer              m_getDataTimer;
    /** ��һ����Ļ��ʾ�Ķ�ʱ�� 
    */
    QTimer              m_nextBarrageTimer;
    /** ��Ļ���ݶ�д���� 
    */
    QMutex              m_barrageMutex;
    /** ��ȡ���ĵ�Ļ���� 
    */
    FMNBarrageStrVec    m_barrageStrVec;
    /** ��ʾ�ĵ�Ļ 
    */
    FMNBarrageItemVec   m_barrageItems;
};

