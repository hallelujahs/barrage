/************************************************************************/
/*	Copyright (c) 2015 FMN. All rights reserved.                        */
/************************************************************************/
#pragma once
#include "FMNConfigManager.h"
#include <QtWidgets/QDialog>


class QSpinBox;
class QButtonGroup;
class QRadioButton;
class QFontComboBox;


/** 设置对话框 
*/
class FMNConfigDlg : public QDialog
{
    Q_OBJECT
public:
    /** 构造函数
    @param [in] pParent 父控件
    */
    FMNConfigDlg(QWidget* pParent = nullptr);


    /** 析构函数 
    */
    ~FMNConfigDlg();


public slots:
    /** 确认事件
    */
    void OnOk();


private:
    /** 当前配置，确认时进行保存 
    */
    FMNConfig       m_config;
    /** 弹幕移动速度
    */
    QSpinBox        *m_moveSpeedSpinBox;
    /** 弹幕移动速度
    */
    QSpinBox        *m_moveSpeedAdjustCharCountSpinBox;
    /** 弹幕移动速度
    */
    QSpinBox        *m_moveSpeedAdjustSpinBox;
    /** 获取弹幕速度 
    */
    QSpinBox        *m_getBarrageSpeedSpinBox;
    /** 弹幕显示行数 
    */
    QSpinBox        *m_showLineCountSpinBox;
    /** 弹幕字体大小 
    */
    QSpinBox        *m_fontSizeSpinBox;
    /** 弹幕字体 
    */
    QFontComboBox   *m_fontFamilyComboBox;
    /** 弹幕颜色 - 红色 
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
    /** 弹幕颜色按钮控制组 
    */
    QButtonGroup    *m_colorBtnGroup;
};


