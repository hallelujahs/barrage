/************************************************************************/
/*	Copyright (c) 2015 FMN. All rights reserved.                        */
/************************************************************************/
#pragma once
#include <QtCore/QTimer>
#include <QtWidgets/QLabel>
#include <vector>
#include <future>


/** ��Ļ��Ϣ
*/
class FMNBarrageItem : public QLabel
{
    Q_OBJECT
public:
    FMNBarrageItem(int y, const QString& text, QTimer* pTimer, QWidget *pParent = 0,
        bool isAdminItem = false);


    ~FMNBarrageItem();


    bool CanBeDelete()
    {return (m_textWidth + x() < m_width / 2);}


    bool ResetItem(const QString& text);


    bool IsExistItem(int posY);


    bool IsItemShowed()
    {return (x() + width() + 100 < m_width);}


    static void SetWidth(int width)
    {m_width = width;}


public slots:
    void MoveOnTime();


private:
    /** ��ǰ��Ļ���
    */
    static int          m_width;
    /** ��Ļ�Ƿ�ɾ�� 
    */
    bool                m_isDelete;
    /** ��Ļ���� 
    */
    int                 m_textWidth;
    /** �ƶ���ʱ��
    */
    QTimer              *m_moveTimer;
    /** ��ǰ��Ļλ�� 
    */
    QPoint              m_labelPnt;
    /** �ƶ��������߳� 
    */
    std::future<void>   m_moveFuture;
};


typedef std::vector<FMNBarrageItem *>     FMNBarrageItemVec;

