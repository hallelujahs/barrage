/************************************************************************/
/*	Copyright (c) 2015 FMN. All rights reserved.                        */
/************************************************************************/
#pragma once
#include <QtWidgets/QMenu>


/** 系统托盘菜单
*/
class FMNSystemTrayMenu : public QMenu
{
    Q_OBJECT
public:
    /** 构造函数
    */
    FMNSystemTrayMenu(QWidget *pParent = nullptr);


    /** 析构函数
    */
    ~FMNSystemTrayMenu();


public slots:
    /** 退出事件
    */
    void OnExit();

    /** 设置事件
    */
    void OnOptions();


private:
    /** 退出事件
    */
    QAction     *m_exitAction;
    /** 设置事件
    */
    QAction     *m_optionsAction;
};

