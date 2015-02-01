/******************************************************************************
 *  版权所有（C）2008-2014，上海二三四五网络科技有限责任公司                  *
 *  保留所有权利。                                                            *
 ******************************************************************************
 *  作者 : 单辉
 *  版本 : 1.0
 *****************************************************************************/
#include "FMNConfigDlg.h"
#include <QtGui/QIcon>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QFontComboBox>
#include <QtWidgets/QDialogButtonBox>


wchar_t const* const CONFIG_DLG_NAME                = L"配置";

wchar_t const* const MOVE_SPEED_NAME                = L"弹幕移动速度";
wchar_t const* const MOVE_SPEED_ADJUST_CHAR_COUNT   = L"速度调整字数";
wchar_t const* const MOVE_SPEED_ADJUST              = L"速度调整大小";
wchar_t const* const GET_BARRAGE_SPEED_NAME         = L"获取弹幕速度";
wchar_t const* const SHOW_LINE_COUNT_NAME           = L"弹幕显示行数";
wchar_t const* const FONT_SIZE_NAME                 = L"弹幕字体大小";
wchar_t const* const FONT_FAMILY_NAME               = L"弹幕字体名称";
wchar_t const* const FONT_COLOR_NAME                = L"弹幕字体颜色";

wchar_t const* const FONT_COLOR_RED                 = L"红色";
wchar_t const* const FONT_COLOR_GREEN               = L"绿色";
wchar_t const* const FONT_COLOR_BLUE                = L"蓝色";
wchar_t const* const FONT_COLOR_CYAN                = L"青色";
wchar_t const* const FONT_COLOR_MAGENTA             = L"品红";
wchar_t const* const FONT_COLOR_YELLOW              = L"黄色";
wchar_t const* const FONT_COLOR_DARKRED             = L"深红色";
wchar_t const* const FONT_COLOR_DARKGREEN           = L"深绿色";
wchar_t const* const FONT_COLOR_DARKBLUE            = L"深蓝色";
wchar_t const* const FONT_COLOR_DARKCYAN            = L"深青色";
wchar_t const* const FONT_COLOR_DARKMAGENTA         = L"暗红色";
wchar_t const* const FONT_COLOR_DARKYELLOW          = L"深黄色";


FMNConfigDlg::FMNConfigDlg(QWidget* pParent /* = nullptr */)
    : QDialog(pParent), m_config(FMNConfigManager::GetInstance()->GetConfig())
{
    // 配置对话框属性
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowIcon(QIcon(":FMNBarrageIcon"));
    setWindowTitle(QString::fromWCharArray(CONFIG_DLG_NAME));
    
    // 配置对话框布局
    QGridLayout* mainLayout = new QGridLayout(this);

    // 移动速度
    int rowCnt = 0;
    mainLayout->addWidget(new QLabel(QString::fromWCharArray(MOVE_SPEED_NAME), this), rowCnt, 0);
    m_moveSpeedSpinBox = new QSpinBox(this);
    m_moveSpeedSpinBox->setRange(1, 1000);
    m_moveSpeedSpinBox->setValue(m_config.MoveSpeed);
    mainLayout->addWidget(m_moveSpeedSpinBox, rowCnt, 1, 1, 3);

    // 少字数速度调整
    ++rowCnt;
    mainLayout->addWidget(new QLabel(QString::fromWCharArray(MOVE_SPEED_ADJUST_CHAR_COUNT), this), rowCnt, 0);
    m_moveSpeedAdjustCharCountSpinBox = new QSpinBox(this);
    m_moveSpeedAdjustCharCountSpinBox->setRange(1, 20);
    m_moveSpeedAdjustCharCountSpinBox->setValue(m_config.MoveSpeedAdjustCharCount);
    mainLayout->addWidget(m_moveSpeedAdjustCharCountSpinBox, rowCnt, 1);
    mainLayout->addWidget(new QLabel(QString::fromWCharArray(MOVE_SPEED_ADJUST), this), rowCnt, 2);
    m_moveSpeedAdjustSpinBox = new QSpinBox(this);
    m_moveSpeedAdjustSpinBox->setRange(-10, 10);
    m_moveSpeedAdjustSpinBox->setValue(m_config.MoveSpeedAdjust);
    mainLayout->addWidget(m_moveSpeedAdjustSpinBox, rowCnt, 3);

    // 获取弹幕的速度
    ++rowCnt;
    mainLayout->addWidget(new QLabel(QString::fromWCharArray(GET_BARRAGE_SPEED_NAME), this), rowCnt, 0);
    m_getBarrageSpeedSpinBox = new QSpinBox(this);
    m_getBarrageSpeedSpinBox->setRange(1, 60000);
    m_getBarrageSpeedSpinBox->setValue(m_config.GetBarrageSpeed);
    mainLayout->addWidget(m_getBarrageSpeedSpinBox, rowCnt, 1, 1, 3);

    // 显示弹幕行数
    ++rowCnt;
    mainLayout->addWidget(new QLabel(QString::fromWCharArray(SHOW_LINE_COUNT_NAME), this), rowCnt, 0);
    m_showLineCountSpinBox = new QSpinBox(this);
    m_showLineCountSpinBox->setRange(1, 50);
    m_showLineCountSpinBox->setValue(m_config.ShowLineCount);
    mainLayout->addWidget(m_showLineCountSpinBox, rowCnt, 1, 1, 3);

    // 弹幕字体大小
    ++rowCnt;
    mainLayout->addWidget(new QLabel(QString::fromWCharArray(FONT_SIZE_NAME), this), rowCnt, 0);
    m_fontSizeSpinBox = new QSpinBox(this);
    m_fontSizeSpinBox->setRange(1, 50);
    m_fontSizeSpinBox->setValue(m_config.FontSize);
    mainLayout->addWidget(m_fontSizeSpinBox, rowCnt, 1, 1, 3);

    // 字体类型
    ++rowCnt;
    mainLayout->addWidget(new QLabel(QString::fromWCharArray(FONT_FAMILY_NAME), this), rowCnt, 0);
    m_fontFamilyComboBox = new QFontComboBox(this);
    m_fontFamilyComboBox->setCurrentFont(QFont(QString::fromStdWString(m_config.FontFamily)));
    mainLayout->addWidget(m_fontFamilyComboBox, rowCnt, 1, 1, 3);

    // 颜色
    ++rowCnt;
    mainLayout->addWidget(new QLabel(QString::fromWCharArray(FONT_COLOR_NAME), this), rowCnt, 0);
    m_colorBtnGroup = new QButtonGroup(this);
    m_redRadioBtn = new QRadioButton(QString::fromWCharArray(FONT_COLOR_RED), this);
    m_greenRadioBtn = new QRadioButton(QString::fromWCharArray(FONT_COLOR_GREEN), this);
    m_blueRadioBtn = new QRadioButton(QString::fromWCharArray(FONT_COLOR_BLUE), this);
    m_cyanRadioBtn = new QRadioButton(QString::fromWCharArray(FONT_COLOR_CYAN), this);
    m_magentaRadioBtn = new QRadioButton(QString::fromWCharArray(FONT_COLOR_MAGENTA), this);
    m_yellowRadioBtn = new QRadioButton(QString::fromWCharArray(FONT_COLOR_YELLOW), this);
    m_darkRedRadioBtn = new QRadioButton(QString::fromWCharArray(FONT_COLOR_DARKRED), this);
    m_darkGreenRadioBtn = new QRadioButton(QString::fromWCharArray(FONT_COLOR_DARKGREEN), this);
    m_darkBlueRadioBtn = new QRadioButton(QString::fromWCharArray(FONT_COLOR_DARKBLUE), this);
    m_darkCyanRadioBtn = new QRadioButton(QString::fromWCharArray(FONT_COLOR_DARKCYAN), this);
    m_darkMagentaRadioBtn = new QRadioButton(QString::fromWCharArray(FONT_COLOR_DARKMAGENTA), this);
    m_darkYellowRadioBtn = new QRadioButton(QString::fromWCharArray(FONT_COLOR_DARKYELLOW), this);

    m_colorBtnGroup->addButton(m_redRadioBtn, FMN_COLOR_RED);
    m_colorBtnGroup->addButton(m_greenRadioBtn, FMN_COLOR_GREEN);
    m_colorBtnGroup->addButton(m_blueRadioBtn, FMN_COLOR_BLUE);
    m_colorBtnGroup->addButton(m_cyanRadioBtn, FMN_COLOR_CYAN);
    m_colorBtnGroup->addButton(m_magentaRadioBtn, FMN_COLOR_MAGENTA);
    m_colorBtnGroup->addButton(m_yellowRadioBtn, FMN_COLOR_YELLOW);
    m_colorBtnGroup->addButton(m_darkRedRadioBtn, FMN_COLOR_DARKRED);
    m_colorBtnGroup->addButton(m_darkGreenRadioBtn, FMN_COLOR_DARKGREEN);
    m_colorBtnGroup->addButton(m_darkBlueRadioBtn, FMN_COLOR_DARKBLUE);
    m_colorBtnGroup->addButton(m_darkCyanRadioBtn, FMN_COLOR_DARKCYAN);
    m_colorBtnGroup->addButton(m_darkMagentaRadioBtn, FMN_COLOR_DARKMAGENTA);
    m_colorBtnGroup->addButton(m_darkYellowRadioBtn, FMN_COLOR_DARKYELLOW);
    m_colorBtnGroup->setExclusive(false);

    mainLayout->addWidget(m_redRadioBtn, rowCnt, 1);
    mainLayout->addWidget(m_greenRadioBtn, rowCnt, 2);
    mainLayout->addWidget(m_blueRadioBtn, rowCnt, 3);
    ++rowCnt;
    mainLayout->addWidget(m_cyanRadioBtn, rowCnt, 1);
    mainLayout->addWidget(m_magentaRadioBtn, rowCnt, 2);
    mainLayout->addWidget(m_yellowRadioBtn, rowCnt, 3);
    ++rowCnt;
    mainLayout->addWidget(m_darkRedRadioBtn, rowCnt, 1);
    mainLayout->addWidget(m_darkGreenRadioBtn, rowCnt, 2);
    mainLayout->addWidget(m_darkBlueRadioBtn, rowCnt, 3);
    ++rowCnt;
    mainLayout->addWidget(m_darkCyanRadioBtn, rowCnt, 1);
    mainLayout->addWidget(m_darkMagentaRadioBtn, rowCnt, 2);
    mainLayout->addWidget(m_darkYellowRadioBtn, rowCnt, 3);

    // 读取配置，并设置按钮状态
    for (int index : m_config.FontColors)
    {
        m_colorBtnGroup->button(index)->setChecked(true);
    }

    // 默认按钮
    ++rowCnt;
    QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    mainLayout->addWidget(buttonBox, rowCnt, 2, 1, 2);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
    connect(this, SIGNAL(accepted()), this, SLOT(OnOk()));

    setLayout(mainLayout);
}


FMNConfigDlg::~FMNConfigDlg()
{
}


void FMNConfigDlg::OnOk()
{
    m_config.MoveSpeed = m_moveSpeedSpinBox->value();
    m_config.MoveSpeedAdjustCharCount = m_moveSpeedAdjustCharCountSpinBox->value();
    m_config.MoveSpeedAdjust = m_moveSpeedAdjustSpinBox->value();
    m_config.GetBarrageSpeed = m_getBarrageSpeedSpinBox->value();
    m_config.ShowLineCount = m_showLineCountSpinBox->value();
    m_config.FontSize = m_fontSizeSpinBox->value();
    m_config.FontFamily = m_fontFamilyComboBox->font().family().toStdWString();

    m_config.FontColors.clear();
    for (QAbstractButton* btn : m_colorBtnGroup->buttons())
    {
        if (btn->isChecked())
        {
            m_config.FontColors.push_back(m_colorBtnGroup->id(btn));
        }
    }

    FMNConfigManager::GetInstance()->GetConfig() = m_config;
    FMNConfigManager::GetInstance()->SaveConfig();
}

