/************************************************************************/
/*	Copyright (c) 2015 FMN. All rights reserved.                        */
/************************************************************************/
#include "FMNBarrage.h"
#include "FMNPathUtility.h"
#include "FMNUniqueProgress.h"
#include <QtCore/QTime>
#include <QtWidgets/QApplication>
#include <QtWidgets/QStyleFactory>
#include <Windows.h>


const wchar_t *const PLUGINS_PATH_NAME = L"plugins\\";
const wchar_t *const PROGRESS_NAME = L"FMNBarrage";


#include "FMNBarrageGetter.h"

int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{
    // ��ֻ֤��һ������
    if (!FMNUniqueProgress::CreateUniqueProgress(PROGRESS_NAME))
    {
        return 0;
    }

    // ����������ʽ
    QApplication::setStyle(QStyleFactory::create("Fusion"));

    // ����ִ�л���
    std::wstring pluginPath;
    FMNPathUtility::GetExeFilePath(pluginPath, PLUGINS_PATH_NAME);
    QApplication::setLibraryPaths(QStringList(QString::fromStdWString(pluginPath)));

    // ��ʼ�������
    QTime curTime = QTime::currentTime();
    qsrand(curTime.msec() + curTime.second() * 1000);

    // ��ʼ��������
    QApplication app(__argc, __argv);
    app.setQuitOnLastWindowClosed(false);
    FMNBarrage barrageWidget;
    barrageWidget.show();

    // ִ��
    return app.exec();
}

