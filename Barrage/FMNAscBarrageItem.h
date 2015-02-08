/************************************************************************/
/*	Copyright (c) 2015 FMN. All rights reserved.                        */
/************************************************************************/
#pragma once
#include <QtCore/QTimer>
#include <QtWidgets/QLabel>
#include <vector>


/** 弹幕信息
*/
class FMNAscBarrageItem : public QLabel
{
    Q_OBJECT
public:
    FMNAscBarrageItem(int y, const QString& text, QTimer* pTimer, 
        QWidget *pParent, Qt::GlobalColor clr = Qt::red);


    ~FMNAscBarrageItem();


    bool CanBeDelete()
    {return (m_textWidth + x() < m_width / 2);}


    bool IsItemShowed()
    {
        return (x() + width() + 100 < m_width);
    }


    static void SetWidth(int width)
    {
        m_width = width;
    }


public slots:
    void MoveOnTime();


private:
    /** 当前屏幕宽度
    */
    static int      m_width;
    /** 弹幕长度
    */
    int             m_textWidth;
    /** 移动定时器
    */
    QTimer*         m_moveTimer;
    /** 当前弹幕位置
    */
    QPoint          m_labelPnt;
};


typedef std::vector<FMNAscBarrageItem *>     FMNAscBarrageItemVec;

