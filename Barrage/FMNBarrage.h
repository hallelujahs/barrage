/************************************************************************/
/*	Copyright (c) 2015 FMN. All rights reserved.                        */
/************************************************************************/
#pragma once
#include "FMNBarrageItem.h"
#include "FMNAscBarrageItem.h"
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


    /** 添加弹幕 
    */
    void AddBarrageItem();


    /** 事件过滤器 
    */
    bool eventFilter(QObject *pObj, QEvent *pEvent);


protected:
    /** 获取下一条弹幕显示的位置
    @param [out] posY 下一条弹幕的位置
    @return true 可以插入弹幕
            false 不能插入
    */
    bool GetNextBarrageItemPos(int& posY);


    /** 删除已显示完毕的弹幕 
    */
    void RemoveShowedItem();


    /** 删除所有弹幕 
    */
    void RemoveAllItem();


    /** 插入管理员弹幕 
    */
    void AddAdminItem(FMNBarrageStr const& barrageStr);


    /** 插入字符画 
    */
    void AddAscPicture(FMNBarrageStr const& barrageStr);


private:
    /** 是否显示 
    */
    bool                    m_isShow;
    /** 显示按钮是否被按下 
    */
    bool                    m_isShowButtonHover;
    /** 显示宽度 
    */
    int                     m_showWidth;
    /** 显示高度 
    */
    int                     m_showHeight;
    /** 显示按钮位置 
    */
    QPoint                  m_showButtonPos;
    /** 托盘图标
    */
    QSystemTrayIcon         *m_systemTrayIcon;
    /** 托盘菜单 
    */
    FMNSystemTrayMenu       *m_systemTrayMenu;
    /** 显示和非显示按钮 
    */
    QToolButton             *m_showCtrlBtn;
    /** 整体布局 
    */
    QVBoxLayout             *m_layout;
    /** 下一条弹幕显示的定时器 
    */
    QTimer                  m_nextBarrageTimer;
    /** 移动定时器
    */
    QTimer                  m_barrageMoveTimer;
    /** 字符画移动定时器
    */
    QTimer                  m_ascBarrageMoveTimer;
    /** 弹幕数据读写保护 
    */
    QMutex                  m_barrageMutex;
    /** 弹幕获取 
    */
    FMNBarrageGetter        m_barrageGetter;
    /** 获取到的弹幕数据 
    */
    FMNBarrageStrVec        m_barrageStrVec;
    /** 显示的弹幕 
    */
    FMNBarrageItemVec       m_barrageItems;
    /** 字符画弹幕 
    */
    FMNAscBarrageItemVec    m_ascBarrageItems;
};

