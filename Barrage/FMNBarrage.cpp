/************************************************************************/
/*	Copyright (c) 2015 FMN. All rights reserved.                        */
/************************************************************************/
#include "FMNBarrage.h"
#include "FMNSystemTrayMenu.h"
#include <QtGui/QPainter>
#include <QtGui/QBitmap>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>



FMNBarrage::FMNBarrage(QWidget *parent)
    : QWidget(parent), m_isShow(true)
{
    // ͸��
    setAutoFillBackground(false);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);
    setAttribute(Qt::WA_TranslucentBackground, true);

    // �ö�
    Qt::WindowFlags flags = windowFlags();
    flags |= Qt::WindowStaysOnTopHint;
    flags ^= Qt::WindowStaysOnBottomHint;
    setWindowFlags(flags);

    // ȫ��
    //this->setFixedSize(500, 500);
    showFullScreen();


    // ����ͼ��Ͳ˵�
    m_systemTrayIcon = new QSystemTrayIcon(this);
    m_systemTrayMenu = new FMNSystemTrayMenu(this);
    m_systemTrayIcon->setIcon(QIcon(":FMNBarrageIcon"));
    m_systemTrayIcon->setContextMenu(m_systemTrayMenu);
    m_systemTrayIcon->show();

    // ��ʾ�ͷ���ʾ����
    m_showCtrlBtn = new QToolButton(this);
    m_showCtrlBtn->setIcon(QIcon(":FMNBarrageIcon"));

    // ����
    m_layout = new QVBoxLayout(this);
    m_layout->setAlignment(Qt::AlignTop);

    QHBoxLayout* showCtrlBtnLayou = new QHBoxLayout(this);
    showCtrlBtnLayou->addWidget(m_showCtrlBtn);
    showCtrlBtnLayou->setAlignment(Qt::AlignRight);
    m_layout->addLayout(showCtrlBtnLayou);

    QVBoxLayout* showLayout = new QVBoxLayout(this);
    m_layout->addLayout(showLayout);

    things = new QLabel(this);
    QFont font;
    font.setFamily(QString::fromWCharArray(L"����"));
    font.setPointSize(30);
    things->setFont(font);
    QPalette pa;
    pa.setColor(QPalette::WindowText, Qt::red);
    things->setPalette(pa);
    things->setText(QString::fromWCharArray(L"��Ļ����~~~~"));
    showLayout->addWidget(things);
    showLayout->setAlignment(Qt::AlignRight);

    curPnt.ry() = 100;
    curPnt.rx() = width();
    things->move(curPnt);

    setLayout(m_layout);
    connect(m_showCtrlBtn, SIGNAL(clicked()), this, SLOT(OnShowCtrlBtn()));
    connect(&m_moveTimer, SIGNAL(timeout()), this, SLOT(MoveOnTime()));

    m_moveTimer.start(10);
}



FMNBarrage::~FMNBarrage()
{
}


void FMNBarrage::OnShowCtrlBtn()
{
    m_isShow = !m_isShow;
    if (m_isShow)
    {
        things->show();
    }
    else
    {
        things->hide();
    }
}


void FMNBarrage::MoveOnTime()
{
    --curPnt.rx();
    things->move(curPnt);
}

