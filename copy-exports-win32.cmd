
rem Copy executables

xcopy build\Debug\Croque-Note.exe         export\win32-vs2008\debug\bin\   /Y
xcopy build\Release\Croque-Note.exe       export\win32-vs2008\release\bin\ /Y

rem Generate i18n template
call i18n\createTemplateStringList.bat

rem Copy i18 files

xcopy i18n\template_en_US.pot             export\all\all\i18n\   /Y
xcopy i18n\fr_FR.po                       export\all\all\i18n\   /Y

if not defined _MASTER_BUILD pause
