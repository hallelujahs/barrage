/************************************************************************/
/*	Copyright (c) 2015 FMN. All rights reserved.                        */
/************************************************************************/
#pragma once
#include <QtCore/QTimer>
#include <QtWidgets/QLabel>
#include <vector>
#include <future>


/** 弹幕信息
*/
class FMNBarrageItem : public QLabel
{
    Q_OBJECT
public:
    FMNBarrageItem(int y, const QString& text, QTimer* pTimer, QWidget *pParent = 0,
        bool isAdminItem = false);


    ~FMNBarrageItem();


    bool CanBeDelete()
    {return (width() + x() < 0);}


    bool ResetItem(const QString& text);


    bool IsExistItem(int posY);


    bool IsItemShowed()
    {return (x() + width() + 100 < m_width);}


    static void SetWidth(int width)
    {m_width = width;}


public slots:
    void MoveOnTime();


private:
    /** 当前屏幕宽度
    */
    static int          m_width;
    bool                m_isDelete;
    /** 移动定时器
    */
    QTimer              *m_moveTimer;
    /** 当前弹幕位置 
    */
    QPoint              m_labelPnt;
    std::future<void>   m_moveFuture;
};


typedef std::vector<FMNBarrageItem *>     FMNBarrageItemVec;

