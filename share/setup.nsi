Name "PENGOLINCOIN Core (64-bit)"

RequestExecutionLevel highest
SetCompressor /SOLID lzma

# General Symbol Definitions
!define REGKEY "SOFTWARE\$(^Name)"
!define COMPANY "PENGOLINCOIN Core project"
!define URL https://www.pengolincoin.xyz/

# MUI Symbol Definitions
!define MUI_ICON "/home/ksk/Works/2020/2020-06/2020-06-23_PengolinCoin/works/Ubuntu_works/pengolincoin-3.2.0/share/pixmaps/pengolincoin.ico"
!define MUI_WELCOMEFINISHPAGE_BITMAP "/home/ksk/Works/2020/2020-06/2020-06-23_PengolinCoin/works/Ubuntu_works/pengolincoin-3.2.0/share/pixmaps/nsis-wizard.bmp"
!define MUI_HEADERIMAGE
!define MUI_HEADERIMAGE_RIGHT
!define MUI_HEADERIMAGE_BITMAP "/home/ksk/Works/2020/2020-06/2020-06-23_PengolinCoin/works/Ubuntu_works/pengolincoin-3.2.0/share/pixmaps/nsis-header.bmp"
!define MUI_FINISHPAGE_NOAUTOCLOSE
!define MUI_STARTMENUPAGE_REGISTRY_ROOT HKLM
!define MUI_STARTMENUPAGE_REGISTRY_KEY ${REGKEY}
!define MUI_STARTMENUPAGE_REGISTRY_VALUENAME StartMenuGroup
!define MUI_STARTMENUPAGE_DEFAULTFOLDER "PENGOLINCOIN Core"
!define MUI_FINISHPAGE_RUN $INSTDIR\pengolincoin-qt
!define MUI_UNICON "${NSISDIR}\Contrib\Graphics\Icons\modern-uninstall.ico"
!define MUI_UNWELCOMEFINISHPAGE_BITMAP "/home/ksk/Works/2020/2020-06/2020-06-23_PengolinCoin/works/Ubuntu_works/pengolincoin-3.2.0/share/pixmaps/nsis-wizard.bmp"
!define MUI_UNFINISHPAGE_NOAUTOCLOSE

# Included files
!include Sections.nsh
!include MUI2.nsh
!include x64.nsh

# Variables
Var StartMenuGroup

# Installer pages
!insertmacro MUI_PAGE_WELCOME
!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_STARTMENU Application $StartMenuGroup
!insertmacro MUI_PAGE_INSTFILES
!insertmacro MUI_PAGE_FINISH
!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES

# Installer languages
!insertmacro MUI_LANGUAGE English

# Installer attributes
OutFile /home/ksk/Works/2020/2020-06/2020-06-23_PengolinCoin/works/Ubuntu_works/pengolincoin-3.2.0/pengolincoin-3.2.0-win64-setup-unsigned.exe
InstallDir $PROGRAMFILES64\PengolinCoin
CRCCheck on
XPStyle on
BrandingText " "
ShowInstDetails show
VIProductVersion 3.2.0.0
VIAddVersionKey ProductName "PENGOLINCOIN Core"
VIAddVersionKey ProductVersion "3.2.0"
VIAddVersionKey CompanyName "${COMPANY}"
VIAddVersionKey CompanyWebsite "${URL}"
VIAddVersionKey FileVersion "3.2.0"
VIAddVersionKey FileDescription "Installer for PENGOLINCOIN Core"
VIAddVersionKey LegalCopyright "Copyright (C) 2015-2021 The PENGOLINCOIN Core developers"
InstallDirRegKey HKCU "${REGKEY}" Path
ShowUninstDetails show

# Installer sections
Section -Main SEC0000
    SetOutPath $INSTDIR
    SetOverwrite on
    File /home/ksk/Works/2020/2020-06/2020-06-23_PengolinCoin/works/Ubuntu_works/pengolincoin-3.2.0/release/pengolincoin-qt
    File /oname=COPYING.txt /home/ksk/Works/2020/2020-06/2020-06-23_PengolinCoin/works/Ubuntu_works/pengolincoin-3.2.0/COPYING
    File /oname=readme.txt /home/ksk/Works/2020/2020-06/2020-06-23_PengolinCoin/works/Ubuntu_works/pengolincoin-3.2.0/doc/README_windows.txt
    SetOutPath $INSTDIR\daemon
    File /home/ksk/Works/2020/2020-06/2020-06-23_PengolinCoin/works/Ubuntu_works/pengolincoin-3.2.0/release/pengolincoind
    File /home/ksk/Works/2020/2020-06/2020-06-23_PengolinCoin/works/Ubuntu_works/pengolincoin-3.2.0/release/pengolincoin-cli
    SetOutPath $INSTDIR\doc
    File /r /home/ksk/Works/2020/2020-06/2020-06-23_PengolinCoin/works/Ubuntu_works/pengolincoin-3.2.0/doc\*.*
    SetOutPath $APPDATA\PENGOLINCOINParams
    File /home/ksk/Works/2020/2020-06/2020-06-23_PengolinCoin/works/Ubuntu_works/pengolincoin-3.2.0/params/sapling-output.params
    File /home/ksk/Works/2020/2020-06/2020-06-23_PengolinCoin/works/Ubuntu_works/pengolincoin-3.2.0/params/sapling-spend.params
    SetOutPath $INSTDIR
    WriteRegStr HKCU "${REGKEY}\Components" Main 1
SectionEnd

Section -post SEC0001
    WriteRegStr HKCU "${REGKEY}" Path $INSTDIR
    SetOutPath $INSTDIR
    WriteUninstaller $INSTDIR\uninstall.exe
    !insertmacro MUI_STARTMENU_WRITE_BEGIN Application
    CreateDirectory $SMPROGRAMS\$StartMenuGroup
    CreateShortcut "$SMPROGRAMS\$StartMenuGroup\$(^Name).lnk" $INSTDIR\pengolincoin-qt
    CreateShortcut "$SMPROGRAMS\$StartMenuGroup\PENGOLINCOIN Core (testnet, 64-bit).lnk" "$INSTDIR\pengolincoin-qt" "-testnet" "$INSTDIR\pengolincoin-qt" 1
    CreateShortcut "$SMPROGRAMS\$StartMenuGroup\Uninstall $(^Name).lnk" $INSTDIR\uninstall.exe
    !insertmacro MUI_STARTMENU_WRITE_END
    WriteRegStr HKCU "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\$(^Name)" DisplayName "$(^Name)"
    WriteRegStr HKCU "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\$(^Name)" DisplayVersion "3.2.0"
    WriteRegStr HKCU "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\$(^Name)" Publisher "${COMPANY}"
    WriteRegStr HKCU "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\$(^Name)" URLInfoAbout "${URL}"
    WriteRegStr HKCU "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\$(^Name)" DisplayIcon $INSTDIR\uninstall.exe
    WriteRegStr HKCU "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\$(^Name)" UninstallString $INSTDIR\uninstall.exe
    WriteRegDWORD HKCU "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\$(^Name)" NoModify 1
    WriteRegDWORD HKCU "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\$(^Name)" NoRepair 1
    WriteRegStr HKCR "pengolincoin" "URL Protocol" ""
    WriteRegStr HKCR "pengolincoin" "" "URL:PengolinCoin"
    WriteRegStr HKCR "pengolincoin\DefaultIcon" "" $INSTDIR\pengolincoin-qt
    WriteRegStr HKCR "pengolincoin\shell\open\command" "" '"$INSTDIR\pengolincoin-qt" "%1"'
SectionEnd

# Macro for selecting uninstaller sections
!macro SELECT_UNSECTION SECTION_NAME UNSECTION_ID
    Push $R0
    ReadRegStr $R0 HKCU "${REGKEY}\Components" "${SECTION_NAME}"
    StrCmp $R0 1 0 next${UNSECTION_ID}
    !insertmacro SelectSection "${UNSECTION_ID}"
    GoTo done${UNSECTION_ID}
next${UNSECTION_ID}:
    !insertmacro UnselectSection "${UNSECTION_ID}"
done${UNSECTION_ID}:
    Pop $R0
!macroend

# Uninstaller sections
Section /o -un.Main UNSEC0000
    Delete /REBOOTOK $INSTDIR\pengolincoin-qt
    Delete /REBOOTOK $INSTDIR\COPYING.txt
    Delete /REBOOTOK $INSTDIR\readme.txt
    RMDir /r /REBOOTOK $INSTDIR\daemon
    RMDir /r /REBOOTOK $INSTDIR\doc
    DeleteRegValue HKCU "${REGKEY}\Components" Main
SectionEnd

Section -un.post UNSEC0001
    DeleteRegKey HKCU "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\$(^Name)"
    Delete /REBOOTOK "$SMPROGRAMS\$StartMenuGroup\Uninstall $(^Name).lnk"
    Delete /REBOOTOK "$SMPROGRAMS\$StartMenuGroup\$(^Name).lnk"
    Delete /REBOOTOK "$SMPROGRAMS\$StartMenuGroup\PENGOLINCOIN Core (testnet, 64-bit).lnk"
    Delete /REBOOTOK "$SMSTARTUP\PengolinCoin.lnk"
    Delete /REBOOTOK $INSTDIR\uninstall.exe
    Delete /REBOOTOK $INSTDIR\debug.log
    Delete /REBOOTOK $INSTDIR\db.log
    DeleteRegValue HKCU "${REGKEY}" StartMenuGroup
    DeleteRegValue HKCU "${REGKEY}" Path
    DeleteRegKey /IfEmpty HKCU "${REGKEY}\Components"
    DeleteRegKey /IfEmpty HKCU "${REGKEY}"
    DeleteRegKey HKCR "pengolincoin"
    RmDir /REBOOTOK $SMPROGRAMS\$StartMenuGroup
    RmDir /REBOOTOK $INSTDIR
    Push $R0
    StrCpy $R0 $StartMenuGroup 1
    StrCmp $R0 ">" no_smgroup
no_smgroup:
    Pop $R0
SectionEnd

# Installer functions
Function .onInit
    InitPluginsDir
    ${If} ${RunningX64}
      ; disable registry redirection (enable access to 64-bit portion of registry)
      SetRegView 64
    ${Else}
      MessageBox MB_OK|MB_ICONSTOP "Cannot install 64-bit version on a 32-bit system."
      Abort
    ${EndIf}
FunctionEnd

# Uninstaller functions
Function un.onInit
    ReadRegStr $INSTDIR HKCU "${REGKEY}" Path
    !insertmacro MUI_STARTMENU_GETFOLDER Application $StartMenuGroup
    !insertmacro SELECT_UNSECTION Main ${UNSEC0000}
FunctionEnd
