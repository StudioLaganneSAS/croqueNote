@echo off
if %1.==. goto :specifyBuild

rem Build the NSIS master installer script, for install and AU
rem ----------------------------------------------------------

:nsis
setLocal EnableDelayedExpansion
set /P MAJOR_VERSION=<MAJOR_VERSION.txt
set /P MINOR_VERSION=<MINOR_VERSION.txt

cd "installer\win32"
makensis -D_%1 /DCN_VERSION=%MAJOR_VERSION%.%MINOR_VERSION% install.nsi
if errorlevel 1 goto nsisError
makensis -D_%1 /DCN_VERSION=%MAJOR_VERSION%.%MINOR_VERSION% update.nsi
if errorlevel 1 goto nsisError
cd "..\.."

rem Copy the built files
rem --------------------

move /Y "installer\win32\CroqueNote-Installer.exe" "export\win32-vs2008\%1\installer"
move /Y "installer\win32\CroqueNote-Updater.exe"   "export\win32-vs2008\%1\installer"

goto :end

:specifyBuild
echo usage: build-installer "Debug|Release"
goto end

:nsisError
echo.
echo.
echo NSIS failed. Aborting.
echo.
echo.
goto end

:end
