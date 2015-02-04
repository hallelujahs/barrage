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
    //HWND hWnd = (HWND)this->winId(); 
    //::SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

    // ȫ��
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
    m_layout->addWidget(m_showCtrlBtn);
    setLayout(m_layout);

    // �¼�����
    connect(m_showCtrlBtn, SIGNAL(clicked()), this, SLOT(OnShowCtrlBtn()));
    connect(&m_getDataTimer, SIGNAL(timeout()), this, SLOT(OnGetData()));
    connect(&m_nextBarrageTimer, SIGNAL(timeout()), this, SLOT(AddBarrageItem()));

    FMNBarrageItem::SetWidth(width());

    m_getDataTimer.start(1000);
    m_nextBarrageTimer.start(10);
    m_nextBarrageTimer.setSingleShot(true);
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


//#include "FMNPathUtility.h"
//#include <fstream>
//#include <codecvt>


void FMNBarrage::OnGetData()
{
    // ������ʾ״̬ʱ�����������ݻ�ȡ
    if (!m_isShow)
    {
        return;
    }

    QMutexLocker mutexLocker(&m_barrageMutex);

    // �ӷ������˻�ȡ���ݣ������浽��ĻVector��
    FMNBarrageGetter barrageGetter;
    barrageGetter.GetBarrage(m_barrageStrVec);

    //std::wstring barrageText;
    //if (!FMNPathUtility::GetExeFilePath(barrageText, L"test.txt"))
    //{
    //    return;
    //}

    //std::locale loc(std::locale(), new std::codecvt_utf8<wchar_t>);
    //std::ifstream ifs(barrageText);
    //ifs.imbue(loc);
    //if (!ifs.good())
    //{
    //    return;
    //}

    //std::string line;
    //while (std::getline(ifs, line))
    //{
    //    m_barrageStrVec.push_back(line);
    //}
    //ifs.close();
}


void FMNBarrage::AddBarrageItem()
{
    FMNConfig& config = FMNConfigManager::GetInstance()->GetConfig();

    // �����Ļ����Ϊ�գ���������ʾ
    if (m_barrageStrVec.empty())
    {
        m_nextBarrageTimer.start((qrand() % 100) * 10);
        return;
    }

    RemoveShowedItem();
    QMutexLocker mutexLocker(&m_barrageMutex);

    int posY = 0;
    if (GetNextBarrageItemPos(posY))
    {
        FMNBarrageItem* item = new FMNBarrageItem(width(), posY,
            QString::fromStdString(m_barrageStrVec.front()), this);
        m_layout->addWidget(item);
        repaint();
        //item->show();
        m_barrageItems.push_back(item);
        m_barrageStrVec.erase(m_barrageStrVec.begin());
    }

    m_nextBarrageTimer.start((qrand() % 100) * 10);
}


bool FMNBarrage::GetNextBarrageItemPos(int& posY)
{
    // ����ʹ�������߶ȣ��ᵼ�����±ߵĵ�Ļ��ʾ������
    posY = qrand() % (height() - 100);

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

    m_barrageItems.clear();
}

