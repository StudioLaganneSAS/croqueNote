bin_PROGRAMS = chordable 

chordable_SOURCES = main.cpp ChordableWindow.h ChordableWindow_XML.h ChordableWindow.cpp ChordableDocument.h ChordableDocument.cpp \
                    ChordableFactory.h ChordableFactory.cpp BarViewVectorControl.h BarViewVectorControl.cpp AddBarsVectorControl.h AddBarsVectorControl.cpp \
		    ChordableSettings.h ChordableSettings.cpp ChordablePreferences.h ChordablePreferences.cpp ChordablePreferences_XML.h

INCLUDES = -I@top_srcdir@ \
	   -I../ \
	   -I../tools \
	   -I../core \
	   -I../ui \
	   -I../music \
	   -I../musicUI \
	   -I../vector \
	   -I../dialogs \
	    @GTK_CFLAGS@ \
	   -D@OSNAME@ -DX86

LDADD = ../dialogs/libdialogs.a ../musicUI/libmusicUI.a ../ui/libui.a ../vector/libvector.a ../core/libcore.a ../tools/libtools.a \
        ../music/libmusic.a -lstdc++ @GTK_LIBS@ @FRAMEWORKS@

