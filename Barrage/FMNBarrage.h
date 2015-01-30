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
    void OnShowCtrlBtn();


    void MoveOnTime();



protected:
    //void paintEvent(QPaintEvent *);



private:
    /** �Ƿ���ʾ 
    */
    bool                    m_isShow;
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

    QTimer                  m_moveTimer;
    QPoint  curPnt;
    QLabel* things;

};

