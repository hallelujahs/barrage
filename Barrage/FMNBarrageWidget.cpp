/************************************************************************/
/*	Copyright (c) 2015 FMN. All rights reserved.                        */
/************************************************************************/
#include "FMNBarrageWidget.h"
#include "FMNPathUtility.h"
#include "FMNSystemTrayMenu.h"
#include "FMNConfigManager.h"
#include <Windows.h>
#include <QtGui/QMouseEvent>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QShortcut>
#include <algorithm>
#include <codecvt>
#include <fstream>
#include <future>


wchar_t const* const FMN_ADMIN_BARRAGE_TAG  = L"<admin>";
size_t FMN_ADMIN_BARRAGE_TAG_LENGTH         = wcslen(FMN_ADMIN_BARRAGE_TAG);
wchar_t const* const FMN_ASC_PICTURE_TAG    = L"<fmn>";
size_t FMN_ASC_PICTURE_TAG_LENGTH           = wcslen(FMN_ASC_PICTURE_TAG);
wchar_t const* const FMN_ASC_PICTURE_PATH   = L"default\\";


HHOOK keyHook = NULL;


LRESULT CALLBACK keyProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    //static BYTE KeyStatus[256] = { 0 };

    //在WH_KEYBOARD_LL模式下lParam 是指向KBDLLHOOKSTRUCT类型地址
    KBDLLHOOKSTRUCT *pkbhs = (KBDLLHOOKSTRUCT *)lParam;
    if ((pkbhs->vkCode == VK_F10/* || pkbhs->vkCode == VK_CONTROL || pkbhs->vkCode == VK_MENU*/) && wParam == WM_KEYUP)
    {
        //memset(KeyStatus, 0, 256 * sizeof(BYTE));
        //GetKeyboardState(KeyStatus);
        //if (KeyStatus[VK_F12] && KeyStatus[VK_CONTROL] && KeyStatus[VK_MENU])
        //{
            FMNBarrageWidget::GetInstance()->OnShowCtrlBtn();
        //}
    }

    //返回1表示截取消息不再传递,返回0表示不作处理,消息继续传递
    return CallNextHookEx(keyHook, nCode, wParam, lParam);
}


FMNBarrageWidgetImpl::FMNBarrageWidgetImpl(QWidget *parent)
    : QWidget(parent), m_isShow(true), m_barrageMutex(), m_barrageStrVec(), 
    m_barrageGetter(&m_barrageMutex, &m_barrageStrVec), m_isShowButtonHover(false)
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
    m_showCtrlBtn->installEventFilter(this);

    // 布局
    m_layout = new QVBoxLayout(this);
    m_layout->setAlignment(Qt::AlignTop);
    m_layout->addWidget(m_showCtrlBtn);
    setLayout(m_layout);

    // 事件关联
    //connect(m_showCtrlBtn, SIGNAL(clicked()), this, SLOT(OnShowCtrlBtn()));
    connect(&m_nextBarrageTimer, SIGNAL(timeout()), this, SLOT(AddBarrageItem()));
    keyHook = SetWindowsHookEx(WH_KEYBOARD_LL, keyProc, GetModuleHandle(nullptr), 0);

    // 其他设置
    m_showWidth = width();
    m_showHeight = height();
    FMNBarrageItem::SetWidth(m_showWidth * 2);
    FMNAscBarrageItem::SetWidth(m_showWidth * 2);
    setMinimumWidth(m_showWidth * 2);
    move(m_showWidth * -1, 0);

    m_nextBarrageTimer.start(10);
    m_barrageMoveTimer.start(10);
}



FMNBarrageWidgetImpl::~FMNBarrageWidgetImpl()
{
    UnhookWindowsHookEx(keyHook);
}


void FMNBarrageWidgetImpl::OnShowCtrlBtn()
{
    m_isShow = !m_isShow;
    m_showCtrlBtn->setDisabled(!m_isShow);
    m_barrageGetter.SetPause(!m_isShow);

    std::for_each(m_barrageItems.begin(), m_barrageItems.end(), [&](FMNBarrageItem *pItem)
    {
        pItem->setVisible(m_isShow);
    });
}


void FMNBarrageWidgetImpl::AddBarrageItem()
{
    if (!isActiveWindow())
    {
        raise();
    }

    if (m_showCtrlBtn->x() < m_showWidth)
    {
        m_showCtrlBtn->move(m_showWidth + 10, 10);
    }

    // 如果弹幕数据为空，不进行显示
    if (!m_isShow || m_barrageStrVec.empty())
    {
        m_nextBarrageTimer.start((qrand() % 100 + 1) * 10);
        return;
    }

    RemoveShowedItem();
    FMNBarrageStr &barrageStr = m_barrageStrVec.front();
    FMNConfig& config = FMNConfigManager::GetInstance()->GetConfig();

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
        int posY = config.ShowLineCount * (config.FontSize + 10);
        if (GetNextBarrageItemPos(posY))
        {
            FMNBarrageItem* item = new FMNBarrageItem(posY,
                QString::fromStdWString(barrageStr), &m_barrageMoveTimer, this);
            m_layout->addWidget(item);
            repaint();
            m_barrageItems.push_back(item);
            QMutexLocker mutexLocker(&m_barrageMutex);
            m_barrageStrVec.erase(m_barrageStrVec.begin());
        }
    }

    m_nextBarrageTimer.start((qrand() % 10 + 1) * 10);
}


bool FMNBarrageWidgetImpl::eventFilter(QObject *pObj, QEvent *pEvent)
{
    static bool isMoved;
    if (pEvent->type() == QEvent::MouseButtonPress)
    {
        isMoved = false;
        QMouseEvent* e = static_cast<QMouseEvent*>(pEvent);
        if (m_showCtrlBtn->rect().contains(e->pos()) && 
            (e->button() == Qt::LeftButton))
        {
            m_showButtonPos = e->pos();
            m_isShowButtonHover = true;
        }
    }
    else if (pEvent->type() == QEvent::MouseMove && m_isShowButtonHover)
    {
        isMoved = true;
        QMouseEvent* e = static_cast<QMouseEvent*>(pEvent);
        int dx = e->pos().x() - m_showButtonPos.x();
        int dy = e->pos().y() - m_showButtonPos.y();
        m_showCtrlBtn->move(m_showCtrlBtn->x() + dx, m_showCtrlBtn->y() + dy);
    }
    else if (pEvent->type() == QEvent::MouseButtonRelease && m_isShowButtonHover)
    {
        m_isShowButtonHover = false;
        if (!isMoved)
        {
            OnShowCtrlBtn();
        }
    }

    return false;
}


bool FMNBarrageWidgetImpl::GetNextBarrageItemPos(int& posY)
{
    // 不能使用完整高度，会导致最下边的弹幕显示不完整
    int showHeight = m_showHeight - 100;
    if (posY != 0 && posY < showHeight)
    {
        showHeight = posY;
    }
    posY = qrand() % showHeight;

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


void FMNBarrageWidgetImpl::RemoveShowedItem()
{
    for (auto itemIter = m_barrageItems.begin(); itemIter != m_barrageItems.end(); ++itemIter)
    {
        if ((*itemIter)->CanBeDelete())
        {
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


void FMNBarrageWidgetImpl::RemoveAllItem()
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


void FMNBarrageWidgetImpl::AddAdminItem(FMNBarrageStr const& barrageStr)
{
    RemoveAllItem();
    FMNBarrageItem* item = new FMNBarrageItem(m_showHeight / 2,
        QString::fromStdWString(barrageStr), &m_barrageMoveTimer, this, true);
    m_layout->addWidget(item);
    repaint();
    m_barrageItems.push_back(item);
}


void FMNBarrageWidgetImpl::AddAscPicture(FMNBarrageStr const& barrageStr)
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

    FMNConfig &config = FMNConfigManager::GetInstance()->GetConfig();
    int posY = m_showHeight / 2 - ascPictureVec.size() / 2 * config.FontSize;
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

