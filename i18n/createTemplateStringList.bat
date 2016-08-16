
rem Create i18n template for croqueNote
import\projectKetchup\win32-vs2008\debug\bin\pki18nlst.exe -i i18n\croqueNoteFolderList.txt -o i18n\template_en_US.pot

rem Merge with i18n template for projectKetchup
type import\projectKetchup\all\all\i18n\projectKetchup_en_US.pot >>  i18n\template_en_US.pot

rem Strip i18n duplicate entries
import\projectKetchup\win32-vs2008\debug\bin\pki18nstrip.exe -i i18n\template_en_US.pot
