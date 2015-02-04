/************************************************************************/
/*	Copyright (c) 2015 FMN. All rights reserved.                        */
/************************************************************************/
#include "FMNBarrage.h"
#include "FMNPathUtility.h"
#include "FMNSystemTrayMenu.h"
#include "FMNConfigManager.h"
#include <Windows.h>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <algorithm>
#include <codecvt>
#include <fstream>
#include <future>


wchar_t const* const FMN_ADMIN_BARRAGE_TAG  = L"<admin>";
size_t FMN_ADMIN_BARRAGE_TAG_LENGTH         = wcslen(FMN_ADMIN_BARRAGE_TAG);
wchar_t const* const FMN_ASC_PICTURE_TAG    = L"<fmn>";
size_t FMN_ASC_PICTURE_TAG_LENGTH           = wcslen(FMN_ASC_PICTURE_TAG);
wchar_t const* const FMN_ASC_PICTURE_PATH   = L"default\\";


FMNBarrage::FMNBarrage(QWidget *parent)
    : QWidget(parent), m_isShow(true), m_barrageMutex(), m_barrageGetter(&m_barrageMutex)
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

    // 事件关联
    connect(m_showCtrlBtn, SIGNAL(clicked()), this, SLOT(OnShowCtrlBtn()));
    connect(&m_getDataTimer, SIGNAL(timeout()), this, SLOT(OnGetData()));
    connect(&m_nextBarrageTimer, SIGNAL(timeout()), this, SLOT(AddBarrageItem()));

    FMNBarrageItem::SetWidth(width());
    FMNAscBarrageItem::SetWidth(width());

    m_getDataTimer.start(1000);
    m_nextBarrageTimer.start(10);
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

    //QMutexLocker mutexLocker(&m_barrageMutex);
    // 从服务器端获取数据，并保存到弹幕Vector中
    m_barrageGetter.GetBarrage(m_barrageStrVec);
}


void FMNBarrage::AddBarrageItem()
{
    FMNConfig& config = FMNConfigManager::GetInstance()->GetConfig();

    // 如果弹幕数据为空，不进行显示
    if (m_barrageStrVec.empty())
    {
        m_nextBarrageTimer.start((qrand() % 100) * 10);
        return;
    }

    RemoveShowedItem();
    FMNBarrageStr &barrageStr = m_barrageStrVec.front();

    if (barrageStr.length() > FMN_ADMIN_BARRAGE_TAG_LENGTH &&
        wcsncmp(FMN_ADMIN_BARRAGE_TAG, &barrageStr[0], FMN_ADMIN_BARRAGE_TAG_LENGTH) == 0)
    {
        // 是否为管理员特殊项
        AddAdminItem(FMNBarrageStr(barrageStr.begin() + FMN_ADMIN_BARRAGE_TAG_LENGTH, barrageStr.end()));
        QMutexLocker mutexLocker(&m_barrageMutex);
        m_barrageStrVec.erase(m_barrageStrVec.begin());
    }
    else if (barrageStr.length() > FMN_ASC_PICTURE_TAG_LENGTH && 
        wcsncmp(FMN_ASC_PICTURE_TAG, &barrageStr[0], FMN_ASC_PICTURE_TAG_LENGTH) == 0)
    {
        // 是否为字符画
        if (m_ascBarrageItems.empty())
        {
            AddAscPicture(FMNBarrageStr(barrageStr.begin() + FMN_ASC_PICTURE_TAG_LENGTH, barrageStr.end()));
            QMutexLocker mutexLocker(&m_barrageMutex);
            m_barrageStrVec.erase(m_barrageStrVec.begin());
        }
    }
    else
    {
        // 普通项
        int posY = 0;
        if (GetNextBarrageItemPos(posY))
        {
            FMNBarrageItem* item = new FMNBarrageItem(posY,
                QString::fromStdWString(barrageStr), this);
            m_layout->addWidget(item);
            repaint();
            m_barrageItems.push_back(item);
            QMutexLocker mutexLocker(&m_barrageMutex);
            m_barrageStrVec.erase(m_barrageStrVec.begin());
        }
    }

    m_nextBarrageTimer.start((qrand() % 100) * 10);
}


bool FMNBarrage::GetNextBarrageItemPos(int& posY)
{
    // 不能使用完整高度，会导致最下边的弹幕显示不完整
    posY = qrand() % (height() - 100);

    if (m_barrageItems.empty())
    {
        return true;
    }

    for (FMNBarrageItem *item : m_barrageItems)
    {
        if (item->IsExistItem(posY) && !item->IsItemShowed())
        {
            return false;
        }
    }

    return true;
}


void FMNBarrage::RemoveShowedItem()
{
    for (auto itemIter = m_barrageItems.begin(); itemIter != m_barrageItems.end(); ++itemIter)
    {
        if ((*itemIter)->CanBeDelete())
        {
            (*itemIter)->hide();
            m_layout->removeWidget(*itemIter);
            delete *itemIter;
            *itemIter = nullptr;

            itemIter = m_barrageItems.erase(itemIter);
            if (itemIter == m_barrageItems.end())
            {
                return;
            }
        }
    }

    for (auto itemIter = m_ascBarrageItems.begin(); itemIter != m_ascBarrageItems.end(); ++itemIter)
    {
        if ((*itemIter)->CanBeDelete())
        {
            (*itemIter)->hide();
            m_layout->removeWidget(*itemIter);
            delete *itemIter;
            *itemIter = nullptr;

            itemIter = m_ascBarrageItems.erase(itemIter);
            if (itemIter == m_ascBarrageItems.end())
            {
                return;
            }
        }
    }
}


void FMNBarrage::RemoveAllItem()
{
    std::for_each(m_barrageItems.begin(), m_barrageItems.end(), [&](FMNBarrageItem* pItem)
    {
        pItem->hide();
        m_layout->removeWidget(pItem);
        delete pItem;
        pItem = nullptr;
    });

    std::for_each(m_ascBarrageItems.begin(), m_ascBarrageItems.end(), [&](FMNAscBarrageItem* pItem)
    {
        pItem->hide();
        m_layout->removeWidget(pItem);
        delete pItem;
        pItem = nullptr;
    });

    m_barrageItems.clear();
    m_ascBarrageItems.clear();
}


void FMNBarrage::AddAdminItem(FMNBarrageStr const& barrageStr)
{
    RemoveAllItem();
    FMNBarrageItem* item = new FMNBarrageItem(height() / 2,
        QString::fromStdWString(barrageStr), this, true);
    m_layout->addWidget(item);
    repaint();
    m_barrageItems.push_back(item);
}


void FMNBarrage::AddAscPicture(FMNBarrageStr const& barrageStr)
{
    std::wstring barrageText;
    if (!FMNPathUtility::GetExeFilePath(barrageText, FMN_ASC_PICTURE_PATH))
    {
        return;
    }
    barrageText += barrageStr;
    barrageText += L".txt";

    std::locale loc(std::locale(), new std::codecvt_utf8<wchar_t>);
    std::wifstream ifs(barrageText);
    ifs.imbue(loc);
    if (!ifs.good())
    {
        return;
    }

    Qt::GlobalColor ascColor = Qt::red;
    FMNBarrageStr line;
    FMNBarrageStrVec ascPictureVec;
    while (std::getline(ifs, line))
    {
        if (ascPictureVec.size() == 0)
        {
            if (line != L"FMN")
            {
                return;
            }
            std::getline(ifs, line);
            ascColor = static_cast<Qt::GlobalColor>(std::stoi(line));
            std::getline(ifs, line);
        }

        ascPictureVec.push_back(line);
    }
    ifs.close();

    m_ascBarrageMoveTimer.stop();

    int posY = height() / 4;
    FMNConfig &config = FMNConfigManager::GetInstance()->GetConfig();
    std::for_each(ascPictureVec.begin(), ascPictureVec.end(), [&](FMNBarrageStr& str)
    {
        FMNAscBarrageItem* item = new FMNAscBarrageItem(posY,
            QString::fromStdWString(str), &m_ascBarrageMoveTimer, this, ascColor);
        m_layout->addWidget(item);
        repaint();
        m_ascBarrageItems.push_back(item);
        posY += item->height();
    });

    int moveSpeed = config.MoveSpeed - config.MoveSpeedAdjust;
    m_ascBarrageMoveTimer.start(moveSpeed);
}

