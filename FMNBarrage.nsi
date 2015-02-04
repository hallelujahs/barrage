; �ýű�ʹ�� HM VNISEdit �ű��༭���򵼲���

; ��װ�����ʼ���峣��
!define PRODUCT_NAME "����ţ��Ļ"
!define PRODUCT_VERSION "6.2"
!define PRODUCT_PUBLISHER "FMN, Inc."
!define PRODUCT_WEB_SITE "http://www.fengmaniu.org/"
!define PRODUCT_DIR_REGKEY "Software\Microsoft\Windows\CurrentVersion\App Paths\Barrage.exe"
!define PRODUCT_UNINST_KEY "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_NAME}"
!define PRODUCT_UNINST_ROOT_KEY "HKLM"

SetCompressor lzma

; ------ MUI �ִ����涨�� (1.67 �汾���ϼ���) ------
!include "MUI.nsh"

; MUI Ԥ���峣��
!define MUI_ABORTWARNING
!define MUI_ICON "Barrage\Resources\FMNBarrageIcon.ico"
!define MUI_UNICON "${NSISDIR}\Contrib\Graphics\Icons\modern-uninstall.ico"

; ��ӭҳ��
!insertmacro MUI_PAGE_WELCOME
; ��װĿ¼ѡ��ҳ��
!insertmacro MUI_PAGE_DIRECTORY
; ��װ����ҳ��
!insertmacro MUI_PAGE_INSTFILES
; ��װ���ҳ��
!define MUI_FINISHPAGE_RUN "$INSTDIR\Barrage.exe"
!insertmacro MUI_PAGE_FINISH

; ��װж�ع���ҳ��
!insertmacro MUI_UNPAGE_INSTFILES

; ��װ�����������������
!insertmacro MUI_LANGUAGE "SimpChinese"

; ��װԤ�ͷ��ļ�
!insertmacro MUI_RESERVEFILE_INSTALLOPTIONS
; ------ MUI �ִ����涨����� ------

Name "${PRODUCT_NAME} ${PRODUCT_VERSION}"
OutFile "����ţ��ĻV6.2.exe"
InstallDir "$PROGRAMFILES\FMNBarrage"
InstallDirRegKey HKLM "${PRODUCT_UNINST_KEY}" "UninstallString"
ShowInstDetails show
ShowUnInstDetails show

Section "MainSection" SEC01
  SetOutPath "$INSTDIR"
  SetOverwrite ifnewer
  File "Win32\Release\Barrage.exe"
  CreateDirectory "$SMPROGRAMS\����ţ��Ļ"
  CreateShortCut "$SMPROGRAMS\����ţ��Ļ\����ţ��Ļ.lnk" "$INSTDIR\Barrage.exe"
  CreateShortCut "$DESKTOP\����ţ��Ļ.lnk" "$INSTDIR\Barrage.exe"
  File "Win32\Release\icudt53.dll"
  File "Win32\Release\icuin53.dll"
  File "Win32\Release\icuuc53.dll"
  File "Win32\Release\msvcp120.dll"
  File "Win32\Release\msvcr120.dll"
  SetOutPath "$INSTDIR\plugins\platforms"
  File "Win32\Release\plugins\platforms\qwindows.dll"
  SetOutPath "$INSTDIR"
  File "Win32\Release\Qt5Core.dll"
  File "Win32\Release\Qt5Gui.dll"
  File "Win32\Release\Qt5Widgets.dll"
  SetOutPath "$INSTDIR\default"
  File "Win32\Release\default\*.*"
SectionEnd

Section -AdditionalIcons
  WriteIniStr "$INSTDIR\${PRODUCT_NAME}.url" "InternetShortcut" "URL" "${PRODUCT_WEB_SITE}"
  CreateShortCut "$SMPROGRAMS\����ţ��Ļ\Website.lnk" "$INSTDIR\${PRODUCT_NAME}.url"
  CreateShortCut "$SMPROGRAMS\����ţ��Ļ\Uninstall.lnk" "$INSTDIR\uninst.exe"
SectionEnd

Section -Post
  WriteUninstaller "$INSTDIR\uninst.exe"
  WriteRegStr HKLM "${PRODUCT_DIR_REGKEY}" "" "$INSTDIR\Barrage.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayName" "$(^Name)"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "UninstallString" "$INSTDIR\uninst.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayIcon" "$INSTDIR\Barrage.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayVersion" "${PRODUCT_VERSION}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "URLInfoAbout" "${PRODUCT_WEB_SITE}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "Publisher" "${PRODUCT_PUBLISHER}"
SectionEnd

/******************************
 *  �����ǰ�װ�����ж�ز���  *
 ******************************/

Section Uninstall
  Delete "$INSTDIR\${PRODUCT_NAME}.url"
  Delete "$INSTDIR\uninst.exe"
  Delete "$INSTDIR\Qt5Widgets.dll"
  Delete "$INSTDIR\Qt5Gui.dll"
  Delete "$INSTDIR\Qt5Core.dll"
  Delete "$INSTDIR\plugins\platforms\qwindows.dll"
  Delete "$INSTDIR\msvcr120.dll"
  Delete "$INSTDIR\msvcp120.dll"
  Delete "$INSTDIR\icuuc53.dll"
  Delete "$INSTDIR\icuin53.dll"
  Delete "$INSTDIR\icudt53.dll"
  Delete "$INSTDIR\Barrage.exe"

  Delete "$SMPROGRAMS\����ţ��Ļ\Uninstall.lnk"
  Delete "$SMPROGRAMS\����ţ��Ļ\Website.lnk"
  Delete "$DESKTOP\����ţ��Ļ.lnk"
  Delete "$SMPROGRAMS\����ţ��Ļ\����ţ��Ļ.lnk"

  RMDir "$SMPROGRAMS\����ţ��Ļ"
  RMDir "$INSTDIR\plugins\platforms"

  RMDir "$INSTDIR"

  DeleteRegKey ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}"
  DeleteRegKey HKLM "${PRODUCT_DIR_REGKEY}"
  SetAutoClose true
SectionEnd

#-- ���� NSIS �ű��༭�������� Function ���α�������� Section ����֮���д���Ա��ⰲװ�������δ��Ԥ֪�����⡣--#

Function un.onInit
  MessageBox MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON2 "��ȷʵҪ��ȫ�Ƴ� $(^Name) ���������е������" IDYES +2
  Abort
FunctionEnd

Function un.onUninstSuccess
  HideWindow
  MessageBox MB_ICONINFORMATION|MB_OK "$(^Name) �ѳɹ��ش���ļ�����Ƴ���"
FunctionEnd
