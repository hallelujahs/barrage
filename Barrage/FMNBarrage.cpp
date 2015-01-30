/************************************************************************/
/*	Copyright (c) 2015 FMN. All rights reserved.                        */
/************************************************************************/
#include "FMNBarrage.h"
#include "FMNSystemTrayMenu.h"
#include <QtCore/QTime>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <algorithm>


const size_t MAX_ITEM_SIZE = 10;


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
    m_layout->setAlignment(Qt::AlignBottom);

    QHBoxLayout* showCtrlBtnLayou = new QHBoxLayout(this);
    showCtrlBtnLayou->addWidget(m_showCtrlBtn);
    showCtrlBtnLayou->setAlignment(Qt::AlignRight);
    m_layout->addLayout(showCtrlBtnLayou);

    //things = new FMNBarrageItem(width(), 100, QString::fromWCharArray(L"��Ļ����~~~~"), &m_moveTimer, this);
    //m_layout->addWidget(things);

    setLayout(m_layout);
    connect(m_showCtrlBtn, SIGNAL(clicked()), this, SLOT(OnShowCtrlBtn()));
    //connect(&m_getDataTimer, SIGNAL(timeout()), this, SLOT(OnGetData()));
    OnGetData();

    FMNBarrageItem::SetWidth(width());

    m_moveTimer.start(10);
    //m_getDataTimer.start(1000);
}



FMNBarrage::~FMNBarrage()
{
}


void FMNBarrage::OnShowCtrlBtn()
{
    m_isShow = !m_isShow;

    std::for_each(m_barrageItems.begin(), m_barrageItems.end(), [&](FMNBarrageItem *pItem)
    {
        pItem->setHidden(m_isShow);
    });
}


QTime time = QTime::currentTime();
void FMNBarrage::OnGetData()
{
    // ������ʾ״̬ʱ�����������ݻ�ȡ
    if (!m_isShow)
    {
        return;
    }

    qsrand(time.msec() + time.second() * 1000);

    AddBarrageItem(QString::fromWCharArray(L"11111111111111111111111111111"));
    AddBarrageItem(QString::fromWCharArray(L"22222222222222222222222222222"));
    AddBarrageItem(QString::fromWCharArray(L"3333333333333333333333333333333"));
    AddBarrageItem(QString::fromWCharArray(L"444444444444444444444444444"));
    AddBarrageItem(QString::fromWCharArray(L"5555555555555555555555555555555555555"));
    AddBarrageItem(QString::fromWCharArray(L"6666666666666666666666666666666666666666666666666666"));
    AddBarrageItem(QString::fromWCharArray(L"7777777777777777777777777777777777777777777777"));
    AddBarrageItem(QString::fromWCharArray(L"888888888888888888888888888"));
    AddBarrageItem(QString::fromWCharArray(L"9999999999999999999999999999999999"));
}


void FMNBarrage::AddBarrageItem(const QString& text)
{
    //if (m_barrageItems.size() > MAX_ITEM_SIZE)
    //{
    //    // ���ҽ����������
    //    while (true)
    //    {
    //        for (FMNBarrageItem* pItem : m_barrageItems)
    //        {
    //            if (pItem->ResetItem(text))
    //            {
    //                return;
    //            }
    //        }
    //    }
    //}
    //else
    {
        // ֱ�Ӳ���
        FMNBarrageItem* item = new FMNBarrageItem(width(), qrand() % height(), text, &m_moveTimer, this);
        m_layout->addWidget(item);
    }
}

