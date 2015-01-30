/************************************************************************/
/*	Copyright (c) 2015 FMN. All rights reserved.                        */
/************************************************************************/
#pragma once
#include "FMNBarrageItem.h"
#include <QtCore/QTimer>
#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSystemTrayIcon>


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


protected:
    void AddBarrageItem(const QString& text);


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
    /** �ƶ���ʱ�� 
    */
    QTimer              m_moveTimer;
    /** ���ݻ�ȡ��ʱ�� 
    */
    QTimer              m_getDataTimer;
    /** ��ʾ�ĵ�Ļ 
    */
    FMNBarrageItemVec   m_barrageItems;
};

