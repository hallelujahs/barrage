/************************************************************************/
/*	Copyright (c) 2015 FMN. All rights reserved.                        */
/************************************************************************/
#include "FMNBarrageItem.h"
#include <QtCore/QTimer>


int FMNBarrageItem::m_width = 0;


FMNBarrageItem::FMNBarrageItem(int x, int y, const QString& text, QTimer *pTimer, 
    QWidget *pParent/* = 0*/)
    : QLabel(pParent), m_labelPnt(x, y)
{
    QFont font;
    font.setFamily(QString::fromWCharArray(L"����"));
    font.setPointSize(30);
    setFont(font);

    QPalette pa;
    pa.setColor(QPalette::WindowText, Qt::red);
    setPalette(pa);

    setText(text);
    move(m_labelPnt);
    connect(pTimer, SIGNAL(timeout()), this, SLOT(MoveOnTime()));
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

