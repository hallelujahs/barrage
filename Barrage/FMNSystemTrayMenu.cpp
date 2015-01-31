/************************************************************************/
/*	Copyright (c) 2015 FMN. All rights reserved.                        */
/************************************************************************/
#include "FMNSystemTrayMenu.h"
#include "FMNConfigDlg.h"
#include <QtWidgets/QApplication>


FMNSystemTrayMenu::FMNSystemTrayMenu(QWidget *pParent /* = nullptr */)
    : QMenu(pParent)
{
    m_optionsAction = new QAction("Options", this);
    m_exitAction = new QAction("Exit", this);

    addAction(m_optionsAction);
    addAction(m_exitAction);

    connect(m_exitAction, SIGNAL(triggered()), this, SLOT(OnExit()));
    connect(m_optionsAction, SIGNAL(triggered()), this, SLOT(OnOptions()));
}


FMNSystemTrayMenu::~FMNSystemTrayMenu()
{

}


void FMNSystemTrayMenu::OnExit()
{
    QApplication::setQuitOnLastWindowClosed(true);
    parentWidget()->setAttribute(Qt::WA_QuitOnClose);
    parentWidget()->close();
}


void FMNSystemTrayMenu::OnOptions()
{
    FMNConfigDlg *m_configDlg = new FMNConfigDlg(this);
    m_configDlg->exec();
}

