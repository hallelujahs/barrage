/************************************************************************/
/*	Copyright (c) 2015 FMN. All rights reserved.                        */
/************************************************************************/
#include "FMNBarrageItem.h"
#include "FMNConfigManager.h"
#include <QtCore/QTimer>


int FMNBarrageItem::m_width = 0;


FMNBarrageItem::FMNBarrageItem(int x, int y, const QString& text, 
    QWidget *pParent/* = 0*/)
    : QLabel(pParent), m_labelPnt(x, y)
{
    FMNConfig& config = FMNConfigManager::GetInstance()->GetConfig();

    QFont font;
    font.setFamily(QString::fromStdWString(config.FontFamily));
    font.setPointSize(config.FontSize);
    setFont(font);

    QPalette pa;
    int clrRand = qrand() % config.FontColors.size();
    pa.setColor(QPalette::WindowText, config.FontColors[qrand() % config.FontColors.size()]);
    setPalette(pa);

    setText(text);
    move(m_labelPnt);

    connect(&m_moveTimer, SIGNAL(timeout()), this, SLOT(MoveOnTime()));

    m_moveTimer.start(config.MoveSpeed - (qrand() % config.MoveSpeedAdjust));
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


void FMNBarrageItem::MoveOnTime()
{
    --m_labelPnt.rx();
    move(m_labelPnt);
}

