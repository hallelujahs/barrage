/************************************************************************/
/*	Copyright (c) 2015 FMN. All rights reserved.                        */
/************************************************************************/
#pragma once
#include "FMNBarrageItem.h"
#include "FMNAscBarrageItem.h"
#include "FMNBarrageGetter.h"
#include "FMNSingleton.h"
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
class FMNBarrageWidgetImpl : public QWidget
{
    Q_OBJECT
public:
    /** ���캯�� 
    */
    FMNBarrageWidgetImpl(QWidget *parent = 0);


    /** �������� 
    */
    ~FMNBarrageWidgetImpl();


    /** ��ʾ�벻��ʾ�л��¼�
    */
    void OnShowCtrlBtn();


public slots:
    /** ��ӵ�Ļ 
    */
    void AddBarrageItem();


    /** �¼������� 
    */
    bool eventFilter(QObject *pObj, QEvent *pEvent);


protected:
    /** ��ȡ��һ����Ļ��ʾ��λ��
    @param [out] posY ��һ����Ļ��λ��
    @return true ���Բ��뵯Ļ
            false ���ܲ���
    */
    bool GetNextBarrageItemPos(int& posY);


    /** ɾ������ʾ��ϵĵ�Ļ 
    */
    void RemoveShowedItem();


    /** ɾ�����е�Ļ 
    */
    void RemoveAllItem();


    /** �������Ա��Ļ 
    */
    void AddAdminItem(FMNBarrageStr const& barrageStr);


    /** �����ַ��� 
    */
    void AddAscPicture(FMNBarrageStr const& barrageStr);


private:
    /** �Ƿ���ʾ 
    */
    bool                    m_isShow;
    /** ��ʾ��ť�Ƿ񱻰��� 
    */
    bool                    m_isShowButtonHover;
    /** ��ʾ��� 
    */
    int                     m_showWidth;
    /** ��ʾ�߶� 
    */
    int                     m_showHeight;
    /** ��ʾ��ťλ�� 
    */
    QPoint                  m_showButtonPos;
    /** ����ͼ��
    */
    QSystemTrayIcon         *m_systemTrayIcon;
    /** ���̲˵� 
    */
    FMNSystemTrayMenu       *m_systemTrayMenu;
    /** ��ʾ�ͷ���ʾ��ť 
    */
    QToolButton             *m_showCtrlBtn;
    /** ���岼�� 
    */
    QVBoxLayout             *m_layout;
    /** ��һ����Ļ��ʾ�Ķ�ʱ�� 
    */
    QTimer                  m_nextBarrageTimer;
    /** �ƶ���ʱ��
    */
    QTimer                  m_barrageMoveTimer;
    /** �ַ����ƶ���ʱ��
    */
    QTimer                  m_ascBarrageMoveTimer;
    /** ��Ļ���ݶ�д���� 
    */
    QMutex                  m_barrageMutex;
    /** ��Ļ��ȡ 
    */
    FMNBarrageGetter        m_barrageGetter;
    /** ��ȡ���ĵ�Ļ���� 
    */
    FMNBarrageStrVec        m_barrageStrVec;
    /** ��ʾ�ĵ�Ļ 
    */
    FMNBarrageItemVec       m_barrageItems;
    /** �ַ�����Ļ 
    */
    FMNAscBarrageItemVec    m_ascBarrageItems;
};


typedef FMNSingleton<FMNBarrageWidgetImpl>  FMNBarrageWidget;

