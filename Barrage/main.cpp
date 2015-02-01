/************************************************************************/
/*	Copyright (c) 2015 FMN. All rights reserved.                        */
/************************************************************************/
#include "FMNBarrage.h"
#include "FMNPathUtility.h"
#include "FMNUniqueProgress.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QStyleFactory>
#include <Windows.h>


const wchar_t *const PLUGINS_PATH_NAME = L"plugins\\";
const wchar_t *const PROGRESS_NAME = L"FMNBarrage";


int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{
    // 保证只有一个进程
    if (!FMNUniqueProgress::CreateUniqueProgress(PROGRESS_NAME))
    {
        return 0;
    }

    // 设置整体样式
    QApplication::setStyle(QStyleFactory::create("Fusion"));

    // 设置执行环境
    std::wstring pluginPath;
    FMNPathUtility::GetExeFilePath(pluginPath, PLUGINS_PATH_NAME);
    QApplication::setLibraryPaths(QStringList(QString::fromStdWString(pluginPath)));

    // 初始化配置文件
    //FMNConfigManager::GetInstance()->LoadConfig();

    // 初始化主窗口
    QApplication app(__argc, __argv);
    app.setQuitOnLastWindowClosed(false);
    FMNBarrage barrageWidget;
    barrageWidget.show();

    // 执行
    return app.exec();
}

