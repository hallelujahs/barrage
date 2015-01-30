/************************************************************************/
/*	Copyright (c) 2015 FMN. All rights reserved.                        */
/************************************************************************/
#pragma once
#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSystemTrayIcon>
#include <QtCore/QTimer>


class QToolButton;
class QVBoxLayout;
class FMNSystemTrayMenu;


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
    void OnShowCtrlBtn();


    void MoveOnTime();



protected:
    //void paintEvent(QPaintEvent *);



private:
    /** 是否显示 
    */
    bool                    m_isShow;
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

    QTimer                  m_moveTimer;
    QPoint  curPnt;
    QLabel* things;

};

