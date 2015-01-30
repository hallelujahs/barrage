/************************************************************************/
/*	Copyright (c) 2015 FMN. All rights reserved.                        */
/************************************************************************/
#include "FMNBarrage.h"
#include "FMNPathUtility.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QStyleFactory>
#include <Windows.h>


const wchar_t *const PLUGINS_PATH_NAME = L"plugins\\";


//int main(int argc, char *argv[])
//{
//    QApplication a(argc, argv);
//    FMNBarrage w;
//    w.show();
//    return a.exec();
//}


int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{
    // 设置整体样式
    QApplication::setStyle(QStyleFactory::create("Fusion"));

    // 设置执行环境
    std::wstring pluginPath;
    FMNPathUtility::GetExeFilePath(pluginPath, PLUGINS_PATH_NAME);
    QApplication::setLibraryPaths(QStringList(QString::fromStdWString(pluginPath)));

    // 初始化主窗口
    QApplication app(__argc, __argv);
    app.setQuitOnLastWindowClosed(false);
    FMNBarrage barrageWidget;
    barrageWidget.show();

    // 执行
    return app.exec();
}

