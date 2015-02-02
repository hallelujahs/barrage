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

    QMutexLocker mutexLocker(&m_barrageMutex);

    // 从服务器端获取数据，并保存到弹幕Vector中
}


void FMNBarrage::AddBarrageItem()
{
    FMNConfig& config = FMNConfigManager::GetInstance()->GetConfig();

    // 如果弹幕数据为空，不进行显示
    if (m_barrageStrVec.empty())
    {
        return;
    }

    QMutexLocker mutexLocker(&m_barrageMutex);


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
        int posY = 0;
        if (GetNextBarrageItemPos(posY))
        {
            FMNBarrageItem* item = new FMNBarrageItem(width(), posY,
                QString::fromStdWString(m_barrageStrVec.front()), this);
            m_layout->addWidget(item);
            m_barrageItems.push_back(item);
            m_barrageStrVec.erase(m_barrageStrVec.begin());
        }

        m_nextBarrageTimer.start((qrand() % 100) * 10);
    }
}


bool FMNBarrage::GetNextBarrageItemPos(int& posY)
{
    posY = qrand() % height();

    if (m_barrageItems.empty())
    {
        return true;
    }

    for (FMNBarrageItem *item : m_barrageItems)
    {
        if (item->IsExistItem(posY))
        {
            return false;
        }
    }

    return true;
}

