/************************************************************************/
/*	Copyright (c) 2015 FMN. All rights reserved.                        */
/************************************************************************/
#pragma once
#include "FMNBarrageItem.h"
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


/** 弹幕窗口 
*/
class FMNBarrage : public QWidget
{
    Q_OBJECT
public:
    /** 构造函数 
    */
    FMNBarrage(QWidget *parent = 0);


    /** 析构函数 
    */
    ~FMNBarrage();



public slots:
    /** 显示与不显示切换事件
    */
    void OnShowCtrlBtn();


    /** 从服务器端获取数据
    */
    void OnGetData();


    /** 添加弹幕 
    */
    void AddBarrageItem();


private:
    typedef std::wstring FMNBarrageStr;
    typedef std::vector<FMNBarrageStr> FMNBarrageStrVec;

    /** 是否显示 
    */
    bool                m_isShow;
    /** 托盘图标
    */
    QSystemTrayIcon     *m_systemTrayIcon;
    /** 托盘菜单 
    */
    FMNSystemTrayMenu   *m_systemTrayMenu;
    /** 显示和非显示按钮 
    */
    QToolButton         *m_showCtrlBtn;
    /** 整体布局 
    */
    QVBoxLayout         *m_layout;
    /** 数据获取定时器 
    */
    QTimer              m_getDataTimer;
    /** 下一条弹幕显示的定时器 
    */
    QTimer              m_nextBarrageTimer;
    /** 获取到的弹幕数据 
    */
    FMNBarrageStrVec    m_barrageStrVec;
    /** 显示的弹幕 
    */
    FMNBarrageItemVec   m_barrageItems;
};

