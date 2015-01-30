/************************************************************************/
/*	Copyright (c) 2015 FMN. All rights reserved.                        */
/************************************************************************/
#pragma once
#include <QtWidgets/QLabel>
#include <vector>


class QTimer;


/** 弹幕信息
*/
class FMNBarrageItem : public QLabel
{
    Q_OBJECT
public:
    FMNBarrageItem(int x, int y, const QString& text, QTimer *pTimer, QWidget *pParent = 0);


    ~FMNBarrageItem();


    bool CanBeDelete()
    {return (width() + m_labelPnt.rx() < 0);}


    bool ResetItem(const QString& text);


    static void SetWidth(int width)
    {m_width = width;}


public slots:
    void MoveOnTime();


private:
    /** 当前屏幕宽度
    */
    static int  m_width;
    /** 当前弹幕位置 
    */
    QPoint      m_labelPnt;
};


typedef std::vector<FMNBarrageItem *>     FMNBarrageItemVec;

