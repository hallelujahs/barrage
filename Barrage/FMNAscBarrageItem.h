/************************************************************************/
/*	Copyright (c) 2015 FMN. All rights reserved.                        */
/************************************************************************/
#pragma once
#include <QtCore/QTimer>
#include <QtWidgets/QLabel>
#include <vector>


/** ��Ļ��Ϣ
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
    /** ��ǰ��Ļ���
    */
    static int      m_width;
    /** ��Ļ����
    */
    int             m_textWidth;
    /** �ƶ���ʱ��
    */
    QTimer*         m_moveTimer;
    /** ��ǰ��Ļλ��
    */
    QPoint          m_labelPnt;
};


typedef std::vector<FMNAscBarrageItem *>     FMNAscBarrageItemVec;

