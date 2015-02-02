/************************************************************************/
/*	Copyright (c) 2015 FMN. All rights reserved.                        */
/************************************************************************/
#include "FMNBarrage.h"
#include "FMNSystemTrayMenu.h"
#include "FMNConfigManager.h"
#include <Windows.h>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <algorithm>
#include <future>


const size_t MAX_ITEM_SIZE = 10;


FMNBarrage::FMNBarrage(QWidget *parent)
    : QWidget(parent), m_isShow(true)
{
    // 透明
    setAutoFillBackground(false);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);
    setAttribute(Qt::WA_TranslucentBackground, true);

    // 置顶
    Qt::WindowFlags flags = windowFlags();
    flags |= Qt::WindowStaysOnTopHint;
    flags ^= Qt::WindowStaysOnBottomHint;
    setWindowFlags(flags);
    //HWND hWnd = (HWND)this->winId(); 
    //::SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

    // 全屏
    //this->setFixedSize(500, 500);
    showFullScreen();


    // 托盘图标和菜单
    m_systemTrayIcon = new QSystemTrayIcon(this);
    m_systemTrayMenu = new FMNSystemTrayMenu(this);
    m_systemTrayIcon->setIcon(QIcon(":FMNBarrageIcon"));
    m_systemTrayIcon->setContextMenu(m_systemTrayMenu);
    m_systemTrayIcon->show();

    // 显示和非显示控制
    m_showCtrlBtn = new QToolButton(this);
    m_showCtrlBtn->setIcon(QIcon(":FMNBarrageIcon"));

    // 布局
    m_layout = new QVBoxLayout(this);
    m_layout->setAlignment(Qt::AlignTop);
    m_layout->addWidget(m_showCtrlBtn);

    setLayout(m_layout);
    connect(m_showCtrlBtn, SIGNAL(clicked()), this, SLOT(OnShowCtrlBtn()));
    connect(&m_getDataTimer, SIGNAL(timeout()), this, SLOT(OnGetData()));
    connect(&m_nextBarrageTimer, SIGNAL(timeout()), this, SLOT(AddBarrageItem()));

    FMNBarrageItem::SetWidth(width());

    m_getDataTimer.start(1000);
    m_nextBarrageTimer.start(10);
    m_nextBarrageTimer.setSingleShot(true);


    m_barrageStrVec.push_back(L"111111111");
    m_barrageStrVec.push_back(L"222222");
    m_barrageStrVec.push_back(L"3333333333333");
    m_barrageStrVec.push_back(L"44444");
    m_barrageStrVec.push_back(L"555555555555555555555");
    m_barrageStrVec.push_back(L"6666666666666");
    m_barrageStrVec.push_back(L"777777777777777");
    m_barrageStrVec.push_back(L"88888888888888888888888888888888");
    m_barrageStrVec.push_back(L"999999999999999999999999999");
}



FMNBarrage::~FMNBarrage()
{
}


void FMNBarrage::OnShowCtrlBtn()
{
    m_isShow = !m_isShow;

    std::for_each(m_barrageItems.begin(), m_barrageItems.end(), [&](FMNBarrageItem *pItem)
    {
        pItem->setVisible(m_isShow);
    });
}


void FMNBarrage::OnGetData()
{
    // 当不显示状态时，不进行数据获取
    if (!m_isShow)
    {
        return;
    }

    //std::async(std::launch::async, [&]()
    //{
        //AddBarrageItem(QString::fromWCharArray(L"11111"));
    //});

    //AddBarrageItem(QString::fromWCharArray(L"2222"));
    //AddBarrageItem(QString::fromWCharArray(L"3333333333"));
    //AddBarrageItem(QString::fromWCharArray(L"444444"));
    //AddBarrageItem(QString::fromWCharArray(L"5555555555555555555555555555555555555"));
    //AddBarrageItem(QString::fromWCharArray(L"6666666666666666666666666666666666666666666666666666"));
    //AddBarrageItem(QString::fromWCharArray(L"7777777777777777777777777777777777777777777777"));
    //AddBarrageItem(QString::fromWCharArray(L"888888888888888888888888888"));
    //AddBarrageItem(QString::fromWCharArray(L"9999999999999999999999999999999999"));
}


void FMNBarrage::AddBarrageItem()
{
    if (m_barrageStrVec.empty())
    {
        return;
    }

    //if (m_barrageItems.size() > MAX_ITEM_SIZE)
    //{
    //    // 查找结束项，并重置
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
        // 直接插入
        FMNBarrageItem* item = new FMNBarrageItem(width(), qrand() % height(), 
            QString::fromStdWString(m_barrageStrVec.front()), this);
        m_layout->addWidget(item);
        m_barrageItems.push_back(item);
        m_barrageStrVec.erase(m_barrageStrVec.begin());

        m_nextBarrageTimer.start((qrand() % 100) * 10);
    }
}

