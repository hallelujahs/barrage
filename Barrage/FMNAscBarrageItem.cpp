/************************************************************************/
/*	Copyright (c) 2015 FMN. All rights reserved.                        */
/************************************************************************/
#include "FMNAscBarrageItem.h"
#include "FMNConfigManager.h"
#include <QtCore/QTimer>
#include <QtCore/QReadLocker>


int FMNAscBarrageItem::m_width = 0;


FMNAscBarrageItem::FMNAscBarrageItem(int y, const QString& text, QTimer* pTimer,
    QWidget *pParent, Qt::GlobalColor clr/* = Qt::red*/)
    : QLabel(text, pParent), m_labelPnt(m_width, y), m_moveTimer(pTimer)
{
    FMNConfig& config = FMNConfigManager::GetInstance()->GetConfig();

    QFont font;
    font.setFamily(QString::fromStdWString(config.FontFamily));
    font.setPointSize(config.FontSize);
    setFont(font);

    QPalette pa;
    int clrRand = qrand() % config.FontColors.size();
    pa.setColor(QPalette::WindowText, clr);
    setPalette(pa);

    move(m_labelPnt);

    connect(m_moveTimer, SIGNAL(timeout()), this, SLOT(MoveOnTime()));
}


FMNAscBarrageItem::~FMNAscBarrageItem()
{
}


void FMNAscBarrageItem::MoveOnTime()
{
    --m_labelPnt.rx();
    move(m_labelPnt);
}

