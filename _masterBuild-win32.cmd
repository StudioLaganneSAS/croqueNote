set _MASTER_BUILD=YES

rem Update the version
call scripts/update-version.bat

rem Call CMake first
call cleanup-project-win32-vs2010.cmd
call generate-project-win32-vs2010.cmd

rem Now build the solution configurations
devenv "build\CroqueNote.sln" /Rebuild "Debug|Win32"
devenv "build\CroqueNote.sln" /Rebuild "Release|Win32"

rem Now build the installers
call scripts\build-installer.bat Debug
call scripts\build-installer.bat Release

rem Now copy exports
call copy-exports-win32.cmd

pause