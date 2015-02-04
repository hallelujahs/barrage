/************************************************************************/
/*	Copyright (c) 2015 FMN. All rights reserved.                        */
/************************************************************************/
#include "FMNBarrageItem.h"
#include "FMNConfigManager.h"
#include <QtCore/QTimer>
#include <QtCore/QReadLocker>
#include <future>


int FMNBarrageItem::m_width = 0;


FMNBarrageItem::FMNBarrageItem(int y, const QString& text, 
    QWidget *pParent/* = 0*/, bool isAdminItem/* = false*/)
    : QLabel(text, pParent), m_labelPnt(m_width, y)
{
    FMNConfig& config = FMNConfigManager::GetInstance()->GetConfig();

    QFont font;
    font.setFamily(QString::fromStdWString(config.FontFamily));
    font.setPointSize(config.FontSize * (isAdminItem ? 2 : 1));
    setFont(font);

    QPalette pa;
    int clrRand = qrand() % config.FontColors.size();
    pa.setColor(QPalette::WindowText, config.FontColors[qrand() % config.FontColors.size()]);
    setPalette(pa);

    move(m_labelPnt);

    connect(&m_moveTimer, SIGNAL(timeout()), this, SLOT(MoveOnTime()));
    m_moveTimer.start(config.MoveSpeed - (qrand() % config.MoveSpeedAdjust));

    //std::async(std::launch::async, [&]()
    //{
    //    Sleep();
    //});
}


FMNBarrageItem::~FMNBarrageItem()
{
}


bool FMNBarrageItem::ResetItem(const QString& text)
{
    if (!CanBeDelete())
    {
        return false;
    }

    setText(text);
    m_labelPnt.rx() = m_width;
    move(m_labelPnt);
    return true;
}


bool FMNBarrageItem::IsExistItem(int posY)
{
    static int moveWidth = m_width - m_width / 3;
    if (x() + width() < moveWidth)
    {
        return false;
    }

    FMNConfig& config = FMNConfigManager::GetInstance()->GetConfig();
    return 
        ((y() <= posY && posY <= y() + height() - config.LineTolerance) || 
        (y() - height() + config.LineTolerance <= posY && posY <= y()));
}


void FMNBarrageItem::MoveOnTime()
{
    //--m_labelPnt.rx();
    move(m_labelPnt);
}

