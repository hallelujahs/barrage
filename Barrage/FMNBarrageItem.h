/************************************************************************/
/*	Copyright (c) 2015 FMN. All rights reserved.                        */
/************************************************************************/
#pragma once
#include <QtCore/QTimer>
#include <QtWidgets/QLabel>
#include <vector>


/** ��Ļ��Ϣ
*/
class FMNBarrageItem : public QLabel
{
    Q_OBJECT
public:
    FMNBarrageItem(int x, int y, const QString& text, QWidget *pParent = 0);


    ~FMNBarrageItem();


    bool CanBeDelete()
    {return (width() + m_labelPnt.rx() < 0);}


    bool ResetItem(const QString& text);


    bool IsExistItem(int posY)
    {return ((y() <= posY && posY <= y() + height()) || (y() - height() <= posY && posY <= y()));}


    bool IsItemShowed()
    {return (x() + width() + 100 < m_width);}


    static void SetWidth(int width)
    {m_width = width;}


public slots:
    void MoveOnTime();


private:
    /** ��ǰ��Ļ���
    */
    static int  m_width;
    /** �ƶ���ʱ��
    */
    QTimer      m_moveTimer;
    /** ��ǰ��Ļλ�� 
    */
    QPoint      m_labelPnt;
};


typedef std::vector<FMNBarrageItem *>     FMNBarrageItemVec;

