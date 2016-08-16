
# Add include directories 

include_directories("${PROJECT_SOURCE_DIR}/src" 
		    "${PROJECT_SOURCE_DIR}/import/projectKetchup/all/all/include")

# Setup WIN32 resources 

if(WIN32)
set(EXTRA_RESOURCES croqueNote.rc)
endif(WIN32)					

# Setup MACOSX resources 

if(APPLE)

set(EXTRA_RESOURCES 

about.png
arrow.png
bar.png
bar_repeat_left.png
bar_repeat_left_down.png
bar_repeat_left_over.png
bar_repeat_left_toggled.png
bar_repeat_left_toggled_down.png
bar_repeat_left_toggled_over.png
bar_repeat_right.png
bar_repeat_right_down.png
bar_repeat_right_over.png
bar_repeat_right_toggled.png
bar_repeat_right_toggled_down.png
bar_repeat_right_toggled_over.png
bar_select.png
bar_small.png
bar_type.png
bar_type_disabled.png
bar_type_down.png
bottom_end.png
bottom_middle.png
bottom_start.png
bottomleft.png
bottomright.png
btm_clicked.png
btm_hover.png
btm_normal.png
btm_toggled_clicked.png
btm_toggled_hover.png
btm_toggled_normal.png
chord_1bar.png
chord_1bar_disabled.png
chord_2bars_1.png
chord_2bars_2.png
chord_3bars1_1.png
chord_3bars1_2.png
chord_3bars1_3.png
chord_3bars2_1.png
chord_3bars2_2.png
chord_3bars2_3.png
chord_4bars_1.png
chord_4bars_2.png
chord_4bars_3.png
chord_4bars_4.png
copy_small.png
cut_small.png
doc_small.png
export.png
export_bkg.png
export_sel.png
export_small.png
globe.png
guitar.png
header.png
help_small.png
info.png
jpeg_64.png
key.png
left_end.png
left_middle.png
left_start.png
markup.png
mid_clicked.png
mid_hover.png
mid_normal.png
mid_toggled_clicked.png
mid_toggled_hover.png
mid_toggled_normal.png
music.png
new.png
new_small.png
notation_down.png
notation_hover.png
notation_normal.png
open.png
open_small.png
options.png
options_small.png
paste_small.png
pdf_64.png
png_64.png
print.png
print_small.png
prius.png
quarter_note.png
redo_small.png
right_end.png
right_middle.png
right_start.png
save.png
save_small.png
search.png
select_all_small.png
sqr_clicked.png
sqr_hover.png
sqr_normal.png
sqr_toggled_clicked.png
sqr_toggled_hover.png
sqr_toggled_normal.png
top_clicked.png
top_end.png
top_hover.png
top_middle.png
top_normal.png
top_start.png
top_toggled_clicked.png
top_toggled_hover.png
top_toggled_normal.png
topleft.png
topright.png
transpose.png
transpose_small.png
tuning.png
undo_small.png

fr_FR.mo

Croque-Note.icns
Croque-Note.png

)

set_source_files_properties(${EXTRA_RESOURCES} PROPERTIES MACOSX_PACKAGE_LOCATION Resources)

endif(APPLE)					

# Setup link libraries for WIN32/MSVC

if(MSVC)

link_directories("${PROJECT_SOURCE_DIR}/import/projectKetchup/win32-vs2008/${CMAKE_CFG_INTDIR}/lib")

link_libraries(

ui.lib 
tools.lib 
core.lib 
music.lib 
musicUI.lib 
dialogs.lib 
vector.lib
Gdiplus.lib
Wininet.lib
Urlmon.lib
Winmm.lib
Comctl32.lib
Msimg32.lib
libpng.lib
libjpeg.lib
zlib.lib
sqlite.lib

)

endif(MSVC)					

# Add libraries & frameworks for Mac
IF(APPLE)

   # TODO: use debug or release subduer based on configuration (HOW?)
   
   set(PNG_LIB "${PROJECT_SOURCE_DIR}/import/projectKetchup/macosx-i386/release/lib/libpng.a")
   set(JPG_LIB "${PROJECT_SOURCE_DIR}/import/projectKetchup/macosx-i386/release/lib/libjpeg.a")
   set(Z_LIB   "${PROJECT_SOURCE_DIR}/import/projectKetchup/macosx-i386/release/lib/libzlib.a")

   set(CORE_LIB     "${PROJECT_SOURCE_DIR}/import/projectKetchup/macosx-i386/release/lib/libcore.a")
   set(DIALOGS_LIB  "${PROJECT_SOURCE_DIR}/import/projectKetchup/macosx-i386/release/lib/libdialogs.a")
   set(MUSIC_LIB    "${PROJECT_SOURCE_DIR}/import/projectKetchup/macosx-i386/release/lib/libmusic.a")
   set(MUSICUI_LIB  "${PROJECT_SOURCE_DIR}/import/projectKetchup/macosx-i386/release/lib/libmusicUI.a")
   set(TOOLS_LIB    "${PROJECT_SOURCE_DIR}/import/projectKetchup/macosx-i386/release/lib/libtools.a")
   set(UI_LIB       "${PROJECT_SOURCE_DIR}/import/projectKetchup/macosx-i386/release/lib/libui.a")
   set(VECTOR_LIB   "${PROJECT_SOURCE_DIR}/import/projectKetchup/macosx-i386/release/lib/libvector.a")


   FIND_LIBRARY(CARBON_LIBRARY Carbon)
   FIND_LIBRARY(CORE_FOUNDATION_LIBRARY CoreFoundation)
   FIND_LIBRARY(CORE_SERVICES_LIBRARY CoreServices)
   FIND_LIBRARY(QUICKTIME_LIBRARY QuickTime)
   FIND_LIBRARY(SQLITE_LIBRARY sqlite3)

   MARK_AS_ADVANCED (CARBON_LIBRARY
		     QUICKTIME_LIBRARY
                     CORE_FOUNDATION_LIBRARY
                     CORE_SERVICES_LIBRARY)

   SET(EXTRA_LIBS 

	${CARBON_LIBRARY} 
	${CORE_FOUNDATION_LIBRARY} 
	${CORE_SERVICES_LIBRARY} 
	${QUICKTIME_LIBRARY} 
	${CORE_LIB}
	${DIALOGS_LIB}
	${MUSIC_LIB}
	${MUSICUI_LIB}
	${TOOLS_LIB}
	${UI_LIB}
	${VECTOR_LIB}
	${SQLITE_LIBRARY} 
	${PNG_LIB} 
	${JPG_LIB} 
	${Z_LIB} )

    link_libraries(${EXTRA_LIBS})

ENDIF (APPLE)
					
# Add main executable

add_executable(Croque-Note WIN32 MACOSX_BUNDLE

AddBarsVectorControl.cpp
AddBarsVectorControl.h
BarHeaderChangeCommand.cpp
BarHeaderChangeCommand.h
BarHeaderSpacer.cpp
BarHeaderSpacer.h
BarSectionNumberChangeCommand.cpp
BarSectionNumberChangeCommand.h
BarViewVectorControl.cpp
BarViewVectorControl.h
ChangeBarTypeCommand.cpp
ChangeBarTypeCommand.h
ChangeBarsPerRowCommand.cpp
ChangeBarsPerRowCommand.h
ChangeKeyCommand.cpp
ChangeKeyCommand.h
ChangeTuningCommand.cpp
ChangeTuningCommand.h
ChordableContentObject.cpp
ChordableContentObject.h
ChordableDocument.cpp
ChordableDocument.h
ChordableFactory.cpp
ChordableFactory.h
ChordablePreferences.cpp
ChordablePreferences.h
ChordableSelection.cpp
ChordableSelection.h
ChordableSettings.cpp
ChordableSettings.h
ChordableVectorControlRoot.cpp
ChordableVectorControlRoot.h
ChordableWindow.cpp
ChordableWindow.h
ChordableWindow_XML.h
ChordablesPreferences_XML.h
ExportDialog.cpp
ExportDialog.h
ExportDialog_XML.h
GenericEditChangeCommand.cpp
GenericEditChangeCommand.h
GenericVectorEditChangeCommand.cpp
GenericVectorEditChangeCommand.h
HideCapoCommand.cpp
HideCapoCommand.h
HideTempoCommand.cpp
HideTempoCommand.h
InsertBarsVectorControl.cpp
InsertBarsVectorControl.h
LineBreakVectorControl.cpp
LineBreakVectorControl.h
ShowCapoCommand.cpp
ShowCapoCommand.h
ShowTempoCommand.cpp
ShowTempoCommand.h
ToggleKeyCommand.cpp
ToggleKeyCommand.h
ToggleRepeatCommand.cpp
ToggleRepeatCommand.h
ToggleSectionMarkerCommand.cpp
ToggleSectionMarkerCommand.h
ToggleShowChordDiagramsCommand.cpp
ToggleShowChordDiagramsCommand.h
ToggleTuningCommand.cpp
ToggleTuningCommand.h
main.cpp

${EXTRA_RESOURCES}

)

# Setup info.pList for Mac Bundle

if(APPLE)

set_target_properties(Croque-Note 
		      PROPERTIES
		      MACOSX_BUNDLE_INFO_PLIST "${PROJECT_SOURCE_DIR}/src/Info.plist")


endif(APPLE)

if(MSVC)

# Also setup manifest additions (common controls, XP-style)

set_target_properties(Croque-Note
		PROPERTIES
		LINK_FLAGS "/MANIFESTDEPENDENCY:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' publicKeyToken='6595b64144ccf1df' language='*' processorArchitecture='*'\""
)

endif(MSVC)					
