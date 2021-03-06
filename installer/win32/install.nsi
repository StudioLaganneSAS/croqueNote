;---------------------
; install.nsi
; Installs Croque-Note
;---------------------

; Uncomment this to force debug builds manually
;!define _DEBUG

;--------------------------------
; Include Modern UI & others

!include "mui2.nsh"
!include "LogicLib.nsh"
!include "strstr.nsh"
!include "WinVer.nsh"
!include "x64.nsh"

;--------------------------------
; Globals

; Version may be defined from command line
!ifndef CROQUE_NOTE_VERSION
!define CROQUE_NOTE_VERSION "0.0"
!endif

!define CN_NAME              "Croque-Note"
!define CN_PUBLISHER         "KetchupApps"
!define CN_COMPANY           "KetchupApps"
!define CN_WEBSITE           "http://www.ketchup-apps.com"
!define CN_UNINSTALLER_PATH  "$INSTDIR\Uninstall.exe"
!define CN_ROOT              "$LOCALAPPDATA\KetchupApps"
!define CN_KEY               "Software\KetchupApps\Croque-Note"

RequestExecutionLevel           user
BrandingText                    " "
Name                            "${CN_NAME}"
Icon                            "..\..\src\croqueNote.ico"
InstallDir                      "${CN_ROOT}\CroqueNote"
OutFile                         "CroqueNote-Installer.exe"

VIProductVersion                "0.0.0.0"
VIAddVersionKey                 /LANG=1033 "ProductName" "Croque-Note"
VIAddVersionKey                 /LANG=1033 "Comments" ""
VIAddVersionKey                 /LANG=1033 "CompanyName" "KetchupApps"
VIAddVersionKey                 /LANG=1033 "LegalCopyright" "© KetchupApps"
VIAddVersionKey                 /LANG=1033 "FileDescription" "KetchupApps"
VIAddVersionKey                 /LANG=1033 "FileVersion" "0.0.0.0"
VIAddVersionKey                 /LANG=1033 "ProductVersion" "v${CN_VERSION}"

Var                             isAlreadyInstalled
Var                             existingInstallDir
Var                             tempTempDir     ; our temporary directory under $TEMP

; -------------------------------
; Define source file roots

!define SrcDirDebug32           "..\..\build\Debug\"
!define SrcDirRelease32         "..\..\build\Release\"

!ifdef _DEBUG
  !define SrcDir32              "${SrcDirDebug32}"
!else
  !define SrcDir32              "${SrcDirRelease32}"
!endif

;--------------------------------
; MUI Config

!define MUI_ABORTWARNING
!define MUI_ICON   "..\..\src\croqueNote.ico"

!define MUI_WELCOMEFINISHPAGE_BITMAP   "installer_banner.bmp"
!define MUI_UNWELCOMEFINISHPAGE_BITMAP "installer_banner.bmp"

;--------------------------------
; Installer Pages

!insertmacro MUI_PAGE_WELCOME
;!insertmacro MUI_PAGE_LICENSE LICENSE.rtf
!insertmacro MUI_PAGE_INSTFILES
!insertmacro MUI_PAGE_FINISH

;--------------------------------
; Uninstaller Pages

!insertmacro MUI_UNPAGE_INSTFILES
!insertmacro MUI_UNPAGE_FINISH

;--------------------------------
; Languages

!insertmacro MUI_LANGUAGE "French"

;--------------------------------
; Init Function

Function .onInit
  
  StrCpy $isAlreadyInstalled "0"
  
  Push $0
  Push $1
  
  ReadRegStr $existingInstallDir HKCU ${CN_KEY} "InstallDir"
  StrCmp $existingInstallDir "" done
  StrCpy $isAlreadyInstalled "1"
  
done:  
  Pop $1
  Pop $0

FunctionEnd

;--------------------------------
; Install success & failed

Function .onInstSuccess
FunctionEnd

;--------------------------------
; Main Section

Section "Croque-Note"
 
  ;
  ; Cleanup if already installed
  ;
 
  ${If} $isAlreadyInstalled == "1"
  
		; Cleanup

		; Remove start menu entries
		SetShellVarContext current
		RMDir /r "$SMPROGRAMS\${CN_NAME}"  

  ${EndIf}
 
  ;
  ; Install the app
  ;

  SetOutPath $INSTDIR
  File "${SrcDir32}Croque-Note.exe"
  
  ; Store installation folder
  WriteRegStr HKCU ${CN_KEY} "InstallDir" $INSTDIR
 
  ; Store current version
  WriteRegStr HKCU ${CN_KEY} "Version" ${CN_VERSION}

  ; Create uninstaller
  WriteUninstaller ${CN_UNINSTALLER_PATH}
  
  ; Write Start Menu shortcuts
  SetShellVarContext current

  CreateDirectory "$SMPROGRAMS\${CN_NAME}"
  CreateShortCut  "$SMPROGRAMS\${CN_NAME}\Uninstall.lnk"  "${CN_UNINSTALLER_PATH}"  
  CreateShortCut  "$SMPROGRAMS\${CN_NAME}\${CN_NAME}.lnk" "$INSTDIR\Croque-Note.exe"  
  
  ; Write uninstall keys

  WriteRegStr   HKCU "Software\Microsoft\Windows\CurrentVersion\Uninstall\Croque-Note" "DisplayName"     "${CN_NAME}"
  WriteRegStr   HKCU "Software\Microsoft\Windows\CurrentVersion\Uninstall\Croque-Note" "DisplayVersion"  "${CN_VERSION}"
  WriteRegStr   HKCU "Software\Microsoft\Windows\CurrentVersion\Uninstall\Croque-Note" "DisplayIcon"     "${CN_UNINSTALLER_PATH}"
  WriteRegStr   HKCU "Software\Microsoft\Windows\CurrentVersion\Uninstall\Croque-Note" "Publisher"       "${CN_PUBLISHER}"
  WriteRegStr   HKCU "Software\Microsoft\Windows\CurrentVersion\Uninstall\Croque-Note" "URLInfoAbout"    "${CN_WEBSITE}"
  WriteRegStr   HKCU "Software\Microsoft\Windows\CurrentVersion\Uninstall\Croque-Note" "UninstallString" "${CN_UNINSTALLER_PATH}"
  
  WriteRegDWORD HKCU "Software\Microsoft\Windows\CurrentVersion\Uninstall\Croque-Note" "NoModify" 1
  WriteRegDWORD HKCU "Software\Microsoft\Windows\CurrentVersion\Uninstall\Croque-Note" "NoRepair" 1

SectionEnd

;--------------------------------
; Uninstaller Section

Function un.onInit
FunctionEnd

Section "Uninstall"

  SetAutoClose true
   
  ; Cleanup
  Delete "$INSTDIR\Croque-Note.exe"

  ; Remove uninstaller
  Delete "${CN_UNINSTALLER_PATH}"

  ; Remove registry keys
  DeleteRegKey HKCU "Software\Microsoft\Windows\CurrentVersion\Uninstall\Croque-Note"
  DeleteRegKey HKCU "${CN_KEY}"

  ; Remove start menu entries
  SetShellVarContext current
  RMDir /r "$SMPROGRAMS\${CN_NAME}"  
  
  ; Remove directories used
  RMDir /r "$INSTDIR"
  
  ; Remove root, only if empty
  RmDir "${CN_ROOT}"

SectionEnd



