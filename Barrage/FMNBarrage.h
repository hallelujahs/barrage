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


protected:
    void AddBarrageItem(const QString& text);


private:
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
    /** 显示的弹幕 
    */
    FMNBarrageItemVec   m_barrageItems;
};

