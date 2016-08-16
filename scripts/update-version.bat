rem Compute the version for the library
rem -----------------------------------

setLocal EnableDelayedExpansion

set /P CN_MAJOR=<MAJOR_VERSION.txt
set /P CN_MINOR=<MINOR_VERSION.txt
set /A CN_MINOR=!CN_MINOR!+1
echo.%CN_MINOR%>MINOR_VERSION.txt

rem Output the version to the header in src/
rem ----------------------------------------

echo.#define CROQUE_NOTE_VERSION "%CN_MAJOR%.%CN_MINOR%">src/CroqueNoteVersion.h

