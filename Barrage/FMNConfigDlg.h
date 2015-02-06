/************************************************************************/
/*	Copyright (c) 2015 FMN. All rights reserved.                        */
/************************************************************************/
#pragma once
#include "FMNConfigManager.h"
#include <QtWidgets/QDialog>


class QSpinBox;
class QLineEdit;
class QButtonGroup;
class QRadioButton;
class QFontComboBox;


/** ���öԻ��� 
*/
class FMNConfigDlg : public QDialog
{
    Q_OBJECT
public:
    /** ���캯��
    @param [in] pParent ���ؼ�
    */
    FMNConfigDlg(QWidget* pParent = nullptr);


    /** �������� 
    */
    ~FMNConfigDlg();


public slots:
    /** ȷ���¼�
    */
    void OnOk();


private:
    /** ��ǰ���ã�ȷ��ʱ���б��� 
    */
    FMNConfig       m_config;
    /** ��������ַ 
    */
    QLineEdit       *m_serverUrlLineEdit;
    /** ��Ļ�ƶ��ٶ�
    */
    QSpinBox        *m_moveSpeedSpinBox;
    /** ��Ļ�ƶ��ٶ�
    */
    QSpinBox        *m_moveSpeedAdjustSpinBox;
    /** ��ȡ��Ļ�ٶ� 
    */
    QSpinBox        *m_getBarrageSpeedSpinBox;
    /** ��Ļ��ʾ���� 
    */
    QSpinBox        *m_showLineCountSpinBox;
    /** �ݲ�ֵ��С
    */
    QSpinBox        *m_lineToleranceSpinBox;
    /** ��Ļ�����С 
    */
    QSpinBox        *m_fontSizeSpinBox;
    /** ��Ļ���� 
    */
    QFontComboBox   *m_fontFamilyComboBox;
    QRadioButton    *m_blackRadioBtn;
    QRadioButton    *m_whiteRadioBtn;
    QRadioButton    *m_darkGrayRadioBtn;
    QRadioButton    *m_grayRadioBtn;
    QRadioButton    *m_lightGrayRadioBtn;
    /** ��Ļ��ɫ - ��ɫ 
    */
    QRadioButton    *m_redRadioBtn;
    QRadioButton    *m_greenRadioBtn;
    QRadioButton    *m_blueRadioBtn;
    QRadioButton    *m_cyanRadioBtn;
    QRadioButton    *m_magentaRadioBtn;
    QRadioButton    *m_yellowRadioBtn;
    QRadioButton    *m_darkRedRadioBtn;
    QRadioButton    *m_darkGreenRadioBtn;
    QRadioButton    *m_darkBlueRadioBtn;
    QRadioButton    *m_darkCyanRadioBtn;
    QRadioButton    *m_darkMagentaRadioBtn;
    QRadioButton    *m_darkYellowRadioBtn;
    /** ��Ļ��ɫ��ť������ 
    */
    QButtonGroup    *m_colorBtnGroup;
};


