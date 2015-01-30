/************************************************************************/
/*	Copyright (c) 2015 FMN. All rights reserved.                        */
/************************************************************************/
#pragma once
#include <QtWidgets/QMenu>


/** ϵͳ���̲˵�
*/
class FMNSystemTrayMenu : public QMenu
{
    Q_OBJECT
public:
    /** ���캯��
    */
    FMNSystemTrayMenu(QWidget *pParent = nullptr);


    /** ��������
    */
    ~FMNSystemTrayMenu();


public slots:
    /** �˳��¼�
    */
    void OnExit();

    /** �����¼�
    */
    void OnOptions();


private:
    /** �˳��¼�
    */
    QAction     *m_exitAction;
    /** �����¼�
    */
    QAction     *m_optionsAction;
};

